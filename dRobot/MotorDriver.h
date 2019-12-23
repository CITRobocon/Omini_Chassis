
#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

/*
 *   Name: MotorDriver
 *   About: A motor driver using PWM-signal
 *
 *   Upward output: None
 *   Upward input:  Duty ratio
 *
 *   Downward output: World
 *   Downward input:  None
 *                _______________
 *      None --> |               | --> MotorDriver/empty
 *               |  MotorDriver  |
 *     World <-- |_______________| <-- MotorDriver/float
 *
 */


#include <cstdint>
#include "common_includes.h"

#include "device.h"
#include "general_msgs/empty_msgs.h"
#include "general_odrs/numeric_odrs.h"


namespace dRobot {


/* Message structure */

// common_msgs/empty_msgs/empty_msg


/* Order structure */

// common_odrs/numeric_odrs/float_odr


/* device class */

class MotorDriver: public device<empty_msg, float_odr> {
	/* Pointers of child device */
	// None

	/* Override: Called back before share a message */
	void msgCallback(empty_msg msg){
	}

	/* Override: Called back after be shared an order */
	void odrCallback(float_odr odr){
		float duty = odr.val;

		duty = saturation(duty);

		if (duty > 0.0f){
			*pwm_ccr_plus = convertTimCCR(duty);
			*pwm_ccr_minus = convertTimCCR(0);
		}
		else if (duty < 0.0f){
			*pwm_ccr_plus = convertTimCCR(0);
			*pwm_ccr_minus = convertTimCCR(duty);
		}
		else{
			*pwm_ccr_plus = convertTimCCR(0);
			*pwm_ccr_minus = convertTimCCR(0);
		}
	}

	/* Personal private variables */
	volatile uint32_t *pwm_ccr_plus;
	volatile uint32_t *pwm_ccr_minus;
	uint32_t pwm_min, pwm_max;
	float max_in;

	/* Personal private functions */
	float saturation(float);
	uint32_t convertTimCCR(float);

public:
	/* Constructor */
	MotorDriver(volatile uint32_t *ccr_p, volatile uint32_t *ccr_m, uint32_t pmin, uint32_t pmax, float imax=0.5f){
		pwm_ccr_plus = ccr_p;
		pwm_ccr_minus = ccr_m;
		pwm_min = pmin;
		pwm_max = pmax;
		max_in = imax;
	}
};


} /* namespace dRobot */

#endif /* MOTORDRIVER_H_ */
