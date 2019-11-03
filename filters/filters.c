/*
 * filters.c
 *
 *  Created on: 2019/11/03
 *      Author: shohei
 */

/* make filter object */

#include "filters.h"

infinite_response_filter_set infinite_response_filter_set_create(float *in_ptr, float *out_ptr, float k){
	infinite_response_filter_set set;

	set.io_ptr.in = in_ptr;
	set.io_ptr.out = out_ptr;
	set.k = k;
	set.base[0] = 0.0;

	return set;
}

finite_response_filter_set finite_response_filter_set_create(float *in_ptr, float *out_ptr, size_t size){
	finite_response_filter_set set;

	set.io_ptr.in = in_ptr;
	set.io_ptr.out = out_ptr;
	set.size = size;

	return set;
}

complementary_filter_set complementary_filter_set_create(float *out_ptr, float *in_high_ptr, float *in_low_ptr, float k){
	complementary_filter_set set;

	set.io_ptr.in_high = in_high_ptr;
	set.io_ptr.in_low = in_low_ptr;
	set.io_ptr.out = out_ptr;
	set.k = k;
	set.base[0] = 0;
	set.base[1] = 0;

	return set;
}


/* filters */

// RC filter: a basic infinite response low pass filter
void RC_filter(infinite_response_filter_set *set){
	set->base[0] = set->k * *(set->io_ptr.in) + (1.0 - set->k) * set->base[0];
	*(set->io_ptr.out) = set->base[0];
}

// LC filter: a basic infinite response high pass filter
void LC_filter(infinite_response_filter_set *set){
	set->base[0] = set->k * *(set->io_ptr.in) + (1.0 - set->k) * set->base[0];
	*(set->io_ptr.out) = *(set->io_ptr.in) - set->base[0];
}

// moving average filter: a finite response low path filter
void moving_average_filter(finite_response_filter_set *set){
	*(set->io_ptr.out) = *(set->io_ptr.in + set->size - 1);

	for (int i = set->size - 1; i > 0; i--){
		*(set->io_ptr.in + i) = *(set->io_ptr.in + i - 1);
		*(set->io_ptr.out) += *(set->io_ptr.in + i - 1);
	}

	*(set->io_ptr.out) /= (float)set->size;
}

void complementary_filter(complementary_filter_set *set){
	set->base[0] = set->k * *(set->io_ptr.in_high) + (1.0 - set->k) * set->base[0];
	float out_high = *(set->io_ptr.in_high) - set->base[0];

	set->base[1] = set->k * *(set->io_ptr.in_low) + (1.0 - set->k) * set->base[1];
	float out_low = set->base[1];

	*(set->io_ptr.out) = out_high + out_low;
}
