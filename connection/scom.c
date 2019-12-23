/*
 * scom.c
 *
 *  Created on: Oct 25, 2019
 *      Author: shohei
 */

#include "scom.h"


/* private variable */

// connections
scom_connection scom_connections_[SCOM_MAX_CONNECTIONS] = {};
int scom_num_connections_ = 0;

// header buffer for sync
uint8_t scom_hbuf_[SCOM_MAX_CONNECTIONS][1];


/* private functions */

// returns invalid connection
const scom_connection scom_invalid_connection(){
	scom_connection invalid_connection;

	invalid_connection.huart_ptr = NULL;
	invalid_connection.index = -1;

	return invalid_connection;
}

// detects error
scom_status scom_error_scan(HAL_StatusTypeDef hal_status){
	switch(hal_status){
	// success
	case HAL_OK:
		return SCOM_SUCCESS;

	// fail
	case HAL_BUSY: // error in calling (multiple call)
		return SCOM_FAIL;

	// unrecoverable error
	case HAL_ERROR:   // error in argument of HAL_UART_??????? (data pointer is NULL or size is Zero)
	case HAL_TIMEOUT: // connection error
	default:          // unexpected error
		return SCOM_ERROR;
	}
}

// reads message including escape sequence
scom_status scom_read_msg(UART_HandleTypeDef *huart_ptr, uint8_t *msg_ptr, int *sum_ptr){
	scom_status status;
	uint8_t rxbuf[1];

	if ((status = scom_error_scan(HAL_UART_Receive(huart_ptr, rxbuf, 1, SCOM_TIMEOUT))) == SCOM_SUCCESS){
		(*sum_ptr) += rxbuf[0];

		if (rxbuf[0] == SCOM_ESCSEQ){
			if ((status = scom_error_scan(HAL_UART_Receive(huart_ptr, rxbuf, 1, SCOM_TIMEOUT))) == SCOM_SUCCESS){
				(*sum_ptr) += rxbuf[0];
				(*msg_ptr) = (rxbuf[0]^SCOM_ESCSEQ);
			}
			else{
				return status;
			}
		}
		else{
			(*msg_ptr) = (rxbuf[0]);
		}
	}
	else{
		return status;
	}

	return SCOM_SUCCESS;
}

// writes message
void scom_write_msg(uint8_t data, uint8_t **msg_ptr, int *sum_ptr){
	if (data == SCOM_ESCSEQ || data == SCOM_HEADER){
		(*sum_ptr) += SCOM_ESCSEQ;
		(*sum_ptr) += data^SCOM_ESCSEQ;

		(**msg_ptr) = SCOM_ESCSEQ;
		(*msg_ptr)++;
		(**msg_ptr) = data^SCOM_ESCSEQ;
		(*msg_ptr)++;
	}
	else{
		(*sum_ptr) += data;

		(**msg_ptr) = data;
		(*msg_ptr)++;
	}
}


/* public functions */

// connects newly
scom_connection scom_connect(UART_HandleTypeDef *huart_ptr){
	scom_connection connection = scom_find_connection(huart_ptr);

	if (!scom_is_valid_connection(connection)){
		if (scom_num_connections_ < SCOM_MAX_CONNECTIONS){
			scom_connections_[scom_num_connections_].huart_ptr = huart_ptr;
			scom_connections_[scom_num_connections_].index = scom_num_connections_;

			connection = scom_connections_[scom_num_connections_];

			scom_num_connections_++;
		}
	}

	return connection;
}

// finds connection by huart pointer
scom_connection scom_find_connection(UART_HandleTypeDef *huart_ptr){
	for (int i = 0; i < scom_num_connections_; i++){
		if (huart_ptr == scom_connections_[i].huart_ptr)
			return scom_connections_[i];
	}

	return scom_invalid_connection();
}

// determines if connection is valid
int scom_is_valid_connection(scom_connection connection){
	if (connection.index != -1){
		return 1;
	}
	else{
		return 0;
	}

}

// returns sync state
scom_status scom_sync_status(scom_connection connection){
	if (scom_hbuf_[connection.index][0] == SCOM_HEADER){
		return SCOM_SUCCESS;
	}
	else{
		return SCOM_FAIL;
	}
}

// tries sync
scom_status scom_sync_try(scom_connection connection){
	scom_hbuf_[connection.index][0] = '\0';
	return scom_error_scan(HAL_UART_Receive(connection.huart_ptr, scom_hbuf_[connection.index], 1, SCOM_TIMEOUT));
}

// wait until sync
void scom_wait_until_sync(scom_connection connection){
	while(scom_sync_status(connection) != SCOM_SUCCESS){
		scom_sync_try(connection);
	}
}

// starts sync with timer interrupt
scom_status scom_sync_start_it(scom_connection connection){
	scom_hbuf_[connection.index][0] = '\0';
	return scom_error_scan(HAL_UART_Receive_IT(connection.huart_ptr, scom_hbuf_[connection.index], 1));
}

// receives
scom_status scom_receive(scom_connection connection, scom_databuf data_buf, int *size_ptr){
	scom_status status;
	*size_ptr = 0;

	if (scom_sync_status(connection) == SCOM_SUCCESS){
		scom_hbuf_[connection.index][0] = '\0';

		int i, sum = 0;
		size_t data_size;

		if ((status = scom_read_msg(connection.huart_ptr, &data_size, &sum)) != SCOM_SUCCESS){
			return status; // receive fail
		}

		uint8_t data[(const size_t) data_size];

		for (i = 0; i < data_size; i++){
			if ((status = scom_read_msg(connection.huart_ptr, data+i, &sum)) != SCOM_SUCCESS){
				return status; // receive fail
			}
		}

		uint8_t checksum[2];

		for (i = 0; i < 2; i++){
			if ((status = scom_read_msg(connection.huart_ptr, checksum+i, NULL)) != SCOM_SUCCESS){
				return status; // receive fail
			}
		}

		if ((sum & 0xFFFF) == ((int)(checksum[0]) | ((int)(checksum[1]) << 8))){
			for (i = 0; i < data_buf.data_size && i < data_size; i++){
				(*(data_buf.data_ptr + i)) = data[i];
			}

			*size_ptr = i;

			return SCOM_SUCCESS;
		}
		else{
			return SCOM_FAIL;  // checksum fail
		}
	}
	else{
		return SCOM_FAIL; // sync fail
	}
}

// transmits
scom_status scom_transmit(scom_connection connection, scom_databuf data_buf){
	int i, sum = 0;
	uint8_t txbuf[(const uint8_t)(1 + 1*2 + data_buf.data_size*2 + 2*2)]; // max length of (header + size + data + checksum)
	uint8_t *txbuf_fptr = txbuf;
	uint8_t **txbuf_pptr = &txbuf_fptr;

	(**txbuf_pptr) = SCOM_HEADER;
	(*txbuf_pptr)++;

	scom_write_msg(data_buf.data_size, txbuf_pptr, &sum);

	for (i = 0; i < data_buf.data_size; i++){
		scom_write_msg(*(data_buf.data_ptr + i), txbuf_pptr, &sum);
	}

	scom_write_msg(sum & 0xFF, txbuf_pptr, NULL);
	scom_write_msg((sum >> 8) & 0xFF, txbuf_pptr, NULL);

	return scom_error_scan(HAL_UART_Transmit(connection.huart_ptr, txbuf, (*txbuf_pptr) - txbuf, SCOM_TIMEOUT));
}


