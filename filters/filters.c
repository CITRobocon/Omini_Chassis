/*
 * filters.c
 *
 *  Created on: 2019/11/03
 *      Author: shohei
 */

/* make filter object */

#include "filters.h"

filters_infinite_response_filter_set filters_infr_filter_set_create(float *in_ptr, float *out_ptr, float k){
	filters_infinite_response_filter_set set;

	set.io_ptr.in = in_ptr;
	set.io_ptr.out = out_ptr;
	set.k = k;
	set.base[0] = 0.0;

	return set;
}

filters_finite_response_filter_set filters_fr_filter_set_create(float *in_ptr, float *out_ptr, size_t size){
	filters_finite_response_filter_set set;

	set.io_ptr.in = in_ptr;
	set.io_ptr.out = out_ptr;
	set.size = size;

	return set;
}

filters_complementary_filter_set filters_complementary_filter_set_create(float *out_ptr, float *in_high_ptr, float *in_low_ptr, float k){
	filters_complementary_filter_set set;

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
void filters_RC_filter(filters_infinite_response_filter_set *set){
	set->base[0] = set->k * *(set->io_ptr.in) + (1.0 - set->k) * set->base[0];
	*(set->io_ptr.out) = set->base[0];
}

// LC filter: a basic infinite response high pass filter
void filters_LC_filter(filters_infinite_response_filter_set *set){
	set->base[0] = set->k * *(set->io_ptr.in) + (1.0 - set->k) * set->base[0];
	*(set->io_ptr.out) = *(set->io_ptr.in) - set->base[0];
}

// moving average filter: a finite response low path filter
void filters_moving_average_filter(filters_finite_response_filter_set *set){
	*(set->io_ptr.out) = *(set->io_ptr.in + set->size - 1);

	for (int i = set->size - 1; i > 0; i--){
		*(set->io_ptr.in + i) = *(set->io_ptr.in + i - 1);
		*(set->io_ptr.out) += *(set->io_ptr.in + i - 1);
	}

	*(set->io_ptr.out) /= (float)set->size;
}

void filters_complementary_filter(filters_complementary_filter_set *set){
	set->base[0] = set->k * *(set->io_ptr.in_high) + (1.0 - set->k) * set->base[0];
	float out_high = *(set->io_ptr.in_high) - set->base[0];

	set->base[1] = set->k * *(set->io_ptr.in_low) + (1.0 - set->k) * set->base[1];
	float out_low = set->base[1];

	*(set->io_ptr.out) = out_high + out_low;
}
