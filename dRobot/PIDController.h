
#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

/*
 *   Name: PIDController
 *   About: A PID-controller
 *
 *   Upward output: None
 *   Upward input:	Target value
 *
 *   Downward output: Input feedback
 *   Downward input:  Feedback value observing
 *
 *                _________________
 *     float --> |                 | --> PIDController/empty
 *               |  PIDController  |
 *     float <-- |_________________| <-- PIDController/float
 *
 */


#include <cstdint>
#include "common_includes.h"

#include "device.h"
#include "general_msgs/empty_msgs.h"
#include "general_msgs/numeric_msgs.h"
#include "general_odrs/empty_odrs.h"
#include "general_odrs/numeric_odrs.h"

namespace dRobot {


/* Message structure */

// common_msgs/empty_msgs/empty_msg


/* Order structure */

// common_odrs/numeric_odrs/float_odr


/* device class */

class PIDController: public device<empty_msg, float_odr> {
public:
	/* Pointers of child device */
	device<empty_msg, float_odr> *output;

protected:
	/* Override: Called back before share a message */
	void msgCallback(empty_msg msg){
	}

	/* Override: Called back after be shared an order */
	void odrCallback(float_odr odr){
		float_odr out_odr;

		prvTick = nowTick;
		nowTick = HAL_GetTick();

		updateErrors(odr.val, static_cast<float>(nowTick - prvTick) * 0.0010);

		out_odr.val = calcInput();

		output->shareOdr(out_odr);
	}

	/* Override: Initialize */
	void initialize(){
		ei = 0.0f;
		e0 = 0.0f;

		nowTick = HAL_GetTick();
	}

	/* Personal private variables */
	float target;
	float p_gain, i_gain, d_gain;
	float ep, ei, ed, e0;

	float i_limit;
	float magnitude_bias;
	float shift_bias;
	uint32_t nowTick;
	uint32_t prvTick;

	/* Personal private functions */
	void updateErrors(float, float);
	float calcInput();

public:
	/* Constructor */
	PIDController(float kp, float ki=0.0f, float kd=0.0f, float limit=0.5f, float magnitude=0.0f, float shift=0.0f){
		p_gain = kp;
		i_gain = ki;
		d_gain = kd;

		i_limit = limit;
		magnitude_bias = magnitude;
		shift_bias = shift;
	}
};


} /* namespace dRobot */

#endif /* PIDCONTROLLER_H_ */
