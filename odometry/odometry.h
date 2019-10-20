/*
 * odometry.h
 *
 *  Created on: Oct 17, 2019
 *      Author: shohei
 */

#ifndef ODOMETRY_H_
#define ODOMETRY_H_

/*
 * Odometry for an omnidirectional chassis with three encoders
 *     ___________________________________________________
 *    |                                                   |
 *    |                   ___                             |
 *    |                  |___| -- left encoder            |
 *    |                    |                              |
 *    |                    |        _                     |
 *    |              O(0,0)|_______| |                    |
 *    |                    |       |_| -- front encoder   |
 *    |   y,j              |                              |
 *    |   ^               _|_                             |
 *    |   :              |___| -- right encoder           |
 *    |   '---> x,i                                       |
 *    |___________________________________________________|
 *   Fig. The initial position of chassis (x = y = theta = 0)
 */

#include <math.h>
#include "stm32f7xx_hal.h"
#include "../physical.h"

// variable parameters
#define ODOMETRY_TIMER_L_ENC TIM1
#define ODOMETRY_TIMER_F_ENC TIM3
#define ODOMETRY_TIMER_R_ENC TIM4

#define ODOMETRY_DIR_L_ENC +
#define ODOMETRY_DIR_F_ENC -
#define ODOMETRY_DIR_R_ENC +

#define ODOMETRY_PPR_ENCWHEEL					PPR_GROUNDING_ENC
#define ODOMETRY_RADIUS_ENCWHEEL				RADIUS_ENC_WHEEL
#define ODOMETRY_DISTANCE_CENTER_TO_ENCWHEEL	DISTANCE_CENTER_TO_ENC_WHEEL;

// an update function
void odometry_update();

// public functions
double odometry_get_x();
double odometry_get_y();
double odometry_get_theta();

double odometry_get_dx_rel();
double odometry_get_dy_rel();
double odometry_get_dtheta();

void odometry_set_position(double, double, double);

#endif /* ODOMETRY_H_ */
