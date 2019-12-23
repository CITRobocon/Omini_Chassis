/*
 * scom.h
 *
 *  Created on: Oct 25, 2019
 *      Author: shohei
 */

#ifndef SCOM_SCOM_H_
#define SCOM_SCOM_H_

#include "stm32f4xx_hal.h"

/*
 *  Serial Communication Protocol
 *
 *    Packet format
 *       1 Byte     - Sync Header(0xFF)
 *       1~2 Byte   - Message Length (N)
 *       N~2N Bytes - Serialized Message Data
 *       2~4 Bytes  - Checksum over Message
 *
 *       0xFF: Sync Header
 *       0xFE: Escape sequence and mask
 *
 *    An example:
 *       Data: 0x00 0xFF 0xFE (3Bytes)
 *
 *       Send packet: | 0xFF | 0x03 | 0x00 | 0xFE | 0xFF^0xFE | 0xFE | 0xFE^0xFE | 0xFE | 0xFE^0xFF | 0x02 |
 *                    |      |      |      |EscSeq| MaskedData|EscSeq| MaskedData|EscSeq| MaskedData|      |
 *                    |      |      | Data1|       Data2      |       Data3      |      LoByte      |HiByte|
 *                    |Header|Length|          SerializedMessageData             |         Checksum        |
 *
 *                     (Checksum = 0xFF + 0x03 + 0xFE + 0xFF^0xFE + 0xFE + 0xFE^0xFE = 0x02FF)
 *                                                      ˜˜˜˜˜˜˜˜˜ 0x01     ˜˜˜˜˜˜˜˜˜ 0x00
 *
 */


/* definitions */

// message format
#define SCOM_HEADER  (0xFF)
#define SCOM_ESCSEQ  (0xFE)
#define SCOM_TIMEOUT (0xFFFF)

// maximum number of connections
#define SCOM_MAX_CONNECTIONS (5)

// initialize with invalid connection
#define SCOM_INVALID_CONNECTION {NULL, -1}

// communication status
typedef enum{
	SCOM_SUCCESS,
	SCOM_FAIL,
	SCOM_ERROR,
}scom_status;


/* structures */

// connection
typedef struct{
	UART_HandleTypeDef *huart_ptr;
	int index;
}scom_connection;

// data type
typedef struct{
	uint8_t *data_ptr;
	size_t data_size;
}scom_databuf;


/* private functions */

// returns invalid connection
scom_connection scom_invalid_connection();

// detects error
scom_status scom_error_scan(HAL_StatusTypeDef);

// reads message including escape sequence
scom_status scom_read_msg(UART_HandleTypeDef*, uint8_t*, int*);

// writes message
void scom_write_msg(uint8_t data, uint8_t**, int*);


/* public functions */

// connects newly
scom_connection scom_connect(UART_HandleTypeDef*);

// finds connection by huart pointer
scom_connection scom_find_connection(UART_HandleTypeDef*);

// determines if connection is valid
int scom_is_valid_connection(scom_connection);

// returns sync state
scom_status scom_sync_status(scom_connection);

// tries sync
scom_status scom_sync_try(scom_connection);

// wait until sync
void scom_wait_until_sync(scom_connection);

// starts sync with timer interrupt
scom_status scom_sync_start_it(scom_connection);

// receives
scom_status scom_receive(scom_connection, scom_databuf, int*);

// transmits
scom_status scom_transmit(scom_connection, scom_databuf);


#endif /* SCOM_SCOM_H_ */
