/*
 * odometry.c
 *
 *  Created on: Oct 17, 2019
 *      Author: shohei
 */

#include "odometry.h"


/* private global variables */

double odometry_x_ = 0.0, odometry_y_ = 0.0, odometry_theta_ = 0.0;
double odometry_c_x_ = 0.0, odometry_c_y_ = 0.0, odometry_c_theta_ = 0.0;		// errors for Kahan summation algorithm
double odometry_dx_rel_ = 0.0, odometry_dy_rel_ = 0.0, odometry_dtheta_ = 0.0;


/* an update function */

void odometry_update(){
	uint16_t bit_cnt_lw = ODOMETRY_TIMER_L_ENC->CNT;
	uint16_t bit_cnt_fw = ODOMETRY_TIMER_F_ENC->CNT;
	uint16_t bit_cnt_rw = ODOMETRY_TIMER_R_ENC->CNT;

	TIM1->CNT -= bit_cnt_lw;
	TIM3->CNT -= bit_cnt_fw;
	TIM4->CNT -= bit_cnt_rw;

	double dlw = ODOMETRY_DIR_L_ENC(double)((bit_cnt_lw>>15)?(-(short)(~bit_cnt_lw)-1):(bit_cnt_lw)) / ODOMETRY_PPR_ENCWHEEL * 2.0*M_PI * ODOMETRY_RADIUS_ENCWHEEL;
	double dfw = ODOMETRY_DIR_F_ENC(double)((bit_cnt_fw>>15)?(-(short)(~bit_cnt_fw)-1):(bit_cnt_fw)) / ODOMETRY_PPR_ENCWHEEL * 2.0*M_PI * ODOMETRY_RADIUS_ENCWHEEL;
	double drw = ODOMETRY_DIR_R_ENC(double)((bit_cnt_rw>>15)?(-(short)(~bit_cnt_rw)-1):(bit_cnt_rw)) / ODOMETRY_PPR_ENCWHEEL * 2.0*M_PI * ODOMETRY_RADIUS_ENCWHEEL;

	odometry_dx_rel_ = (drw + dlw) / 2.0;
	odometry_dy_rel_ = dfw - (drw - dlw) / 2.0;
	odometry_dtheta_ = (drw - dlw) / 2.0 / ODOMETRY_DISTANCE_CENTER_TO_ENCWHEEL;

	// Kahan summation algorithm
	double y, t;

	y = odometry_dx_rel_*cos(odometry_theta_ + 0.5*odometry_dtheta_) - odometry_dy_rel_*sin(odometry_theta_ + 0.5*odometry_dtheta_) - odometry_c_x_;
	t = odometry_x_ + y;
	odometry_c_x_ = (t - odometry_x_) - y;
	odometry_x_ = t;

	y = odometry_dx_rel_*sin(odometry_theta_ + 0.5*odometry_dtheta_) + odometry_dy_rel_*cos(odometry_theta_ + 0.5*odometry_dtheta_) - odometry_c_y_;
	t = odometry_y_ + y;
	odometry_c_y_ = (t - odometry_y_) - y;
	odometry_y_ = t;

	y = odometry_dtheta_ - odometry_c_theta_;
	t = odometry_theta_ + y;
	odometry_c_theta_ = (t - odometry_theta_) - y;
	odometry_theta_ = t;

	if (odometry_theta_ < -M_PI){
		odometry_theta_ += 2.0*M_PI;
	}
	else if (odometry_theta_ > M_PI){
		odometry_theta_ -= 2.0*M_PI;
	}

	return;
}


/* public functions */

double odometry_get_x(){
	return odometry_x_;
}

double odometry_get_y(){
	return odometry_y_;
}

double odometry_get_theta(){
	return odometry_theta_;
}

double odometry_get_dx_rel(){
	return odometry_dx_rel_;
}

double odometry_get_dy_rel(){
	return odometry_dy_rel_;
}

double odometry_get_dtheta(){
	return odometry_dtheta_;
}

void odometry_set_position(double x0, double y0, double theta0){
	odometry_x_ = x0;
	odometry_y_ = y0;
	odometry_theta_ = theta0;

	odometry_c_x_ = 0.0;
	odometry_c_y_ = 0.0;
	odometry_c_theta_ = 0.0;

	return;
}
