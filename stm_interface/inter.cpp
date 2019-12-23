/*
 * inter.cpp
 *
 *  Created on: Dec 17, 2019
 *      Author: shohei
 */

#include "inter.h"

/* Private variables */

// Number of registered inter_tag
uint8_t inter_num_tags_ = 0;

// List of registered inter_tag
inter_tag inter_tags_[INTER_MAX_TAGS] = {};

// List of registered function and inter_arg with tag
void (*inter_functions_[INTER_MAX_TAGS])(inter_arg);
inter_arg inter_args_[INTER_MAX_TAGS] = {};


/* Public functions */

void inter_register(const char *str, void (*fptr)(inter_arg), void *arg){
	if (inter_num_tags_ >= INTER_MAX_TAGS)
		return;

	for (int i = 0; i < 4 && *(str+i) != '\n'; i++){
		inter_tags_[inter_num_tags_].name.as_str[i] = *(str+i);
	}

	inter_tags_[inter_num_tags_].index = inter_num_tags_;

	inter_functions_[inter_num_tags_] = fptr;

	inter_args_[inter_num_tags_].argptr = arg;

	inter_num_tags_++;
}

void inter_call(const char *str){
	union{
		char as_str[4];
		uint32_t as_val;
	} name;

	for (int i = 0; i < 4 && *(str+i) != '\n'; i++){
		name.as_str[i] = *(str+i);
	}

	for (int i = 0; i < inter_num_tags_; i++){
		if (inter_tags_[i].name.as_val == name.as_val)
			(*inter_functions_[i])(inter_args_[i]);
	}
}
