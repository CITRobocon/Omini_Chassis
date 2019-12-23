/*
 * inter.h
 *
 *  Created on: Dec 18, 2019
 *      Author: shohei
 */

#ifndef INTER_H_
#define INTER_H_


#include <stdint.h>
#include "common_includes.h"


/* Definitions */

// Number of registrable tags
#define INTER_MAX_TAGS 10

#define INTER_FIND(str) static void (*fptr)()=NULL; if(fptr==NULL){fptr=inter_find(str);}
#define INTER_CALL		if(fptr!=NULL){(*fptr)();}


/* Structures */

// inter_tag structure
typedef struct{
	union{
		char as_str[4];
		uint32_t as_val;
	} name;
	int index;
}inter_tag;

// inter_arg structure
typedef struct{
	void *argptr;
} inter_arg;


/* Public functions */

void inter_register(const char*, void (inter_arg), void*);


#ifdef __cplusplus
extern "C"{
#endif

void inter_call(const char*);

#ifdef __cplusplus
}
#endif


#endif /* INTER_H_ */
