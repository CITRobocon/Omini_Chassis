/*
 * numeric_msg.h
 *
 *  Created on: 2019/12/16
 *      Author: shohei
 */

#ifndef GENERAL_MSGS_NUMERIC_MSGS_H_
#define GENERAL_MSGS_NUMERIC_MSGS_H_


typedef struct{
	float val;
} float_msg;


typedef struct{
	uint8_t val;
} uint8_msg;


typedef struct{
	size_t size;
	float *array;
} float_array_msg;


typedef struct{
	size_t size;
	float *array;
} uint8_array_msg;


#endif /* GENERAL_MSGS_NUMERIC_MSGS_H_ */
