/*
 * ticker.h
 *
 *  Created on: Oct 20, 2019
 *      Author: shohei
 */

#ifndef TICKER_TICKER_H_
#define TICKER_TICKER_H_

#include <stdlib.h>
#include "stm32f7xx_hal.h"


/* a definition  */
#define TICKER_MAX_TASKS 10

/* ticker structures */

typedef struct{
	// call period in millisecond
	uint32_t period_ms;

	// void pointer of argument
	void *argptr;
}ticker_args;

typedef struct{
	// function and its argument pointer
	void (*fptr)(ticker_args);
	void *argptr;

	// processing priority
	int priority;

	// counter period
	unsigned int counter_period;

	// period for argument
	uint32_t prev_tick;
}ticker_task;

/* a private function */
// comparing function for qsort in stdlib
int ticker_task_priority_compare(const void*, const void*);

/* public functions */
// create ticker_task structure
ticker_task ticker_task_create(void (ticker_args), void*, int, double, char);

// initialize
void ticker_init(TIM_HandleTypeDef*, int, char);

// assign a new task
void ticker_assign(void (ticker_args), void*, int, double, char);

// assign a task
void ticker_assign_task(ticker_task);

// schedule timer interrupt
void ticker_schedule();

// start interrupt
void ticker_start();

// stop interrupt
void ticker_stop();

// calling function
void ticker_call();

#endif /* TICKER_TICKER_H_ */
