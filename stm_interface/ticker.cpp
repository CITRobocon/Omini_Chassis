/*
 * ticker.cpp
 *
 *  Created on: 2019/12/16
 *      Author: shohei
 */


#include "ticker.h"
#include <cmath>

/* private global variables */

// timer configurations: timer handler pointer, clock frequency
TIM_HandleTypeDef *ticker_htim_ptr_ = NULL;
unsigned int ticker_clock_frequency_ = 0;			// maximum: 4.29GHz (range of unsigned int)

// interrupt setting: interrupt period, interrupt counter, counter period, call
unsigned int ticker_it_counter_period_ = 0;
unsigned int ticker_counter_ = 0;
unsigned int ticker_counter_period_ = 0;
unsigned int ticker_call_counter_ = 0;

// tasks
unsigned int ticker_num_tasks_ = 0;
unsigned int ticker_num_scheduled_tasks_ = 0;
ticker_task ticker_tasks_[TICKER_MAX_TASKS] = {};


/* a private function */

// comparing function for qsort in stdlib
int ticker_task_priority_compare(const void *a, const void *b){
	return ((ticker_task*)a)->priority - ((ticker_task*)b)->priority;
}


/* public functions */

// create ticker_task structure
ticker_task ticker_task_create(void (*fptr)(ticker_args), void *argptr, int priority, double cycle, char unit){
	ticker_task task;

	task.fptr = fptr;
	task.argptr = argptr;
	task.priority = priority;

	switch (unit){
	case 's':

		task.counter_period = (unsigned int)(std::round(ticker_clock_frequency_ * cycle));
		break;

	case 'f':
	default:
		task.counter_period = ticker_clock_frequency_ / (unsigned int)(std::round(cycle));
	}

	return task;
}

// initialize
void ticker_init(TIM_HandleTypeDef *htim_ptr, int timer_frequency, char unit){
	ticker_htim_ptr_ = htim_ptr;
	ticker_num_tasks_ = 0;
	ticker_num_scheduled_tasks_ = 0;

	ticker_it_counter_period_ = 1;
	ticker_counter_ = 0;
	ticker_counter_period_ = 1;
	ticker_call_counter_ = 0;

	switch(unit){
	case 'm':
		ticker_clock_frequency_ = timer_frequency * 1000000;
		return;

	case 'k':
		ticker_clock_frequency_ = timer_frequency * 1000;
		return;

	case ' ':
	default:
		ticker_clock_frequency_ = timer_frequency;
		return;
	}
}

// assign new task
void ticker_assign(void (*fptr)(ticker_args), void *argptr, int priority, double cycle, char unit){
	if (ticker_num_tasks_ < TICKER_MAX_TASKS){
		ticker_tasks_[ticker_num_tasks_].fptr = fptr;
		ticker_tasks_[ticker_num_tasks_].argptr = argptr;
		ticker_tasks_[ticker_num_tasks_].priority = priority;

		switch (unit){
		case 's':
			ticker_tasks_[ticker_num_tasks_].counter_period = (unsigned int)(std::round(ticker_clock_frequency_ * cycle));
			break;

		case 'f':
		default:
			ticker_tasks_[ticker_num_tasks_].counter_period = ticker_clock_frequency_ / (unsigned int)(std::round(cycle));
		}

		ticker_num_tasks_++;
	}
}

// assign task
void ticker_assign_task(ticker_task task){
	if (ticker_num_tasks_ < TICKER_MAX_TASKS){
		ticker_tasks_[ticker_num_tasks_] = task;
		ticker_num_tasks_++;
	}
}

// schedule timer interrupt
void ticker_schedule(void){
	qsort(ticker_tasks_, ticker_num_tasks_, sizeof(ticker_task), ticker_task_priority_compare);

	unsigned int min_c_period = ticker_clock_frequency_, max_c_period = 0;
	unsigned int i, j;

	if (ticker_num_tasks_ > 0){
		min_c_period = ticker_tasks_[0].counter_period;
		max_c_period = ticker_tasks_[0].counter_period;

		for (i = 1; i < ticker_num_tasks_; i++){
			if(ticker_tasks_[i].counter_period < min_c_period){
				min_c_period = ticker_tasks_[i].counter_period;
			}
			else if (ticker_tasks_[i].counter_period > max_c_period){
				max_c_period = ticker_tasks_[i].counter_period;
			}
		}
	}

	ticker_it_counter_period_ = 1;
	unsigned int scaler = 1;

	// 2 is 1st and the only even prime number
	while(1){
		for (i = 0; i < ticker_num_tasks_; i++){
			if ((ticker_tasks_[i].counter_period / ticker_it_counter_period_) % 2 != 0)
				break;
		}

		if (i == ticker_num_tasks_){
			ticker_it_counter_period_ *= 2;
			if (scaler * 2 <= 0xFFFF)
				scaler *= 2;
		}
		else{
			break;
		}
	}

	for (i = 3; i <= min_c_period / ticker_it_counter_period_; i += 2){
		while(1){
			for (j = 0; j < ticker_num_tasks_; j++){
				if ((ticker_tasks_[j].counter_period / ticker_it_counter_period_) % i != 0)
					break;
			}

			if (j == ticker_num_tasks_){
				ticker_it_counter_period_ *= i;
				if (scaler * i <= 0xFFFF)
					scaler *= i;
			}
			else{
				break;
			}
		}
	}

	ticker_counter_period_ = max_c_period / ticker_it_counter_period_;

	// HAL setting
	ticker_htim_ptr_->Init.Prescaler = scaler - 1;
	ticker_htim_ptr_->Init.Period = ticker_it_counter_period_ / scaler;
	if (HAL_TIM_Base_Init(ticker_htim_ptr_) != HAL_OK){
		while(1);
	}

	ticker_num_scheduled_tasks_ = ticker_num_tasks_;
}

// start interrupt
void ticker_start(){
	uint32_t tick = HAL_GetTick();

	for (unsigned int i = 0; i < ticker_num_scheduled_tasks_; i++)
		ticker_tasks_[i].prev_tick = tick;

	if (HAL_TIM_Base_Start_IT(ticker_htim_ptr_) != HAL_OK){
		while(1);
	}
}

// stop interrupt
void ticker_stop(){
	HAL_TIM_Base_Stop_IT(ticker_htim_ptr_);
}

// calling function
void ticker_call(){
	ticker_counter_++;

	uint32_t now_tick;
	ticker_args t_args;

	if (ticker_counter_ == ticker_counter_period_){
		ticker_counter_ = 0;
	}

	for (ticker_call_counter_ = 0; ticker_call_counter_ < ticker_num_scheduled_tasks_; ticker_call_counter_++){
		if ((ticker_it_counter_period_ * ticker_counter_) % ticker_tasks_[ticker_call_counter_].counter_period == 0){
			now_tick = HAL_GetTick();

			t_args.period_ms = now_tick - ticker_tasks_[ticker_call_counter_].prev_tick;
			t_args.argptr = ticker_tasks_[ticker_call_counter_].argptr;

			ticker_tasks_[ticker_call_counter_].prev_tick = now_tick;

			(*(ticker_tasks_[ticker_call_counter_].fptr))(t_args);
		}
	}
}


