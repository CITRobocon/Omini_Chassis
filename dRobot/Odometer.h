
#ifndef ODOMETER_H_
#define ODOMETER_H_

/*
 *   Name: Odometer
 *   About: An odometer with wheel and encoder
 *
 *   Upward output: Displacement of wheel
 *   Upward input:	None
 *
 *   Downward output: None
 *   Downward input:  World
 *                ____________
 *     World --> |            | --> Odometer/float
 *               |  Odometer  |
 *      None <-- |____________| <-- Odometer/empty
 *
 */


#include <cstdint>
#include "common_includes.h"

#include "device.h"
#include "general_msgs/numeric_msgs.h"
#include "general_odrs/empty_odrs.h"

namespace dRobot {


/* Message structure */

// common_msgs/numeric_msgs/float_msg


/* Order structure */

// common_odrs/empty_odrs/empty_odr


/* device class */

class Odometer: public device<float_msg, empty_odr> {
	/* Pointers of child device */
	// None

	/* Override: Called back before share a message */
	void msgCallback(float_msg msg){
		myMsg.val = getWheelDisplacement();
	}

	/* Override: Called back after be shared an order */
	void odrCallback(empty_odr odr){
		enc_counter->CNT = 0;
	}

	/* Personal private variables */
	TIM_TypeDef *enc_counter;
	float enc_ppr;
	float wheel_radius;

	/* Personal private functions */
	float getAndResetEncRotate();
	float getWheelDisplacement();

public:
	/* Constructor */
	Odometer(TIM_TypeDef* counter, float ppr, float radius){
		enc_counter = counter;
		enc_ppr = ppr;
		wheel_radius = radius;
	}
};


} /* namespace dRobot */

#endif /* ODOMETER_H_ */
