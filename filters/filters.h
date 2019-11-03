/*
 * filters.h
 *
 *  Created on: 2019/11/03
 *      Author: shohei
 */

#ifndef FILTERS_FILTERS_H_
#define FILTERS_FILTERS_H_

#include <stddef.h>

// low level filter sets based on filters_io_ptr
typedef struct{
	struct{
		float *in;
		float *out;
	}io_ptr;

	float k;
	float base[1];
}filters_infinite_response_filter_set;

typedef struct{
	struct{
		float *in;
		float *out;
	}io_ptr;

	size_t size;
}filters_finite_response_filter_set;

// high level filter sets
typedef struct{
	struct{
		float *in_high;
		float *in_low;
		float *out;
	}io_ptr;

	float k;
	float base[2];
}filters_complementary_filter_set;


/* make filter object */

filters_infinite_response_filter_set filters_infr_filter_set_create(float*, float*, float);

filters_finite_response_filter_set filters_fr_filter_set_create(float*, float*, size_t);

filters_complementary_filter_set filters_complementary_filter_set_create(float*, float*, float*, float);


/* filters */

// RC filter: a basic infinite response low pass filter
void filters_RC_filter(filters_infinite_response_filter_set*);

// LC filter: a basic infinite response high pass filter
void filters_LC_filter(filters_infinite_response_filter_set*);

// moving average filter: a finite response low path filter
void filters_moving_average_filter(filters_finite_response_filter_set*);

void filters_complementary_filter(filters_complementary_filter_set*);
