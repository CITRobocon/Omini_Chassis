/*
 * filters.h
 *
 *  Created on: 2019/11/03
 *      Author: shohei
 */

#ifndef FILTERS_FILTERS_H_
#define FILTERS_FILTERS_H_

#include <stddef.h>


/* structures */

typedef struct{
	struct{
		float *in;
		float *out;
	}io_ptr;

	float k;
	float base[1];
}infinite_response_filter_set;

typedef struct{
	struct{
		float *in;
		float *out;
	}io_ptr;

	size_t size;
}finite_response_filter_set;

// high level filter sets
typedef struct{
	struct{
		float *in_high;
		float *in_low;
		float *out;
	}io_ptr;

	float k;
	float base[2];
}complementary_filter_set;


/* make filter object */

infinite_response_filter_set infinite_response_filter_set_create(float*, float*, float);

finite_response_filter_set finite_response_filter_set_create(float*, float*, size_t);

complementary_filter_set complementary_filter_set_create(float*, float*, float*, float);


/* filters */

// RC filter: a basic infinite response low pass filter
void RC_filter(infinite_response_filter_set*);

// LC filter: a basic infinite response high pass filter
void LC_filter(infinite_response_filter_set*);

// moving average filter: a finite response low path filter
void moving_average_filter(finite_response_filter_set*);

void complementary_filter(complementary_filter_set*);


#endif /* FILTERS_FILTERS_H_ */
