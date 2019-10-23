/*
 * timer_it_manager.h
 *
 *  Created on: Oct 20, 2019
 *      Author: shohei
 */

#ifndef TICKER_TICKER_H_
#define TICKER_TICKER_H_

#include <stdlib.h>
#include "stm32f7xx_hal.h"

#define MAX_TASKS 10


/* a structure */

typedef struct{
	void (*fptr)(void);
	int priority;
	unsigned int counter_period;
}ticker_task;


/* a private function */

// comparing function for qsort in stdlib
int ticker_task_priority_compare(const void*, const void*);


/* public functions */

// create ticker_task structure
ticker_task ticker_task_create(void (void), int, double, char);

// initialize
void ticker_init(TIM_HandleTypeDef*, int, char);

// assign a new task
void ticker_assign(void (void), int, double, char);

// assign a task
void ticker_assign_task(ticker_task);

// run
void ticker_run();

// calling function
void ticker_call();


#endif /* TICKER_TICKER_H_ */