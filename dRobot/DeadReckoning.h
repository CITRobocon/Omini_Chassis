
#ifndef DEADRECKONING_H_
#define DEADRECKONING_H_

/*
 *   Name: DeadReckoning
 *   About: A dead reckoning system with three odometer
 *
 *   Upward output:   2D pose from fixed origin
 *   Upward input:	  None
 *
 *   Downward output: None
 *   Downward input:  displacement of odometer x3
 *                _________________
 *     twist --> |                 | --> DeadReckoning/pose2d
 *               |  DeadReckoning  |
 *     empty <-- |_________________| <-- DeadReckoning/empty
 *
 */

#include "device.h"
#include "tf/tf.h"
#include "general_msgs/geometry_msgs.h"
#include "general_odrs/empty_odrs.h"

namespace dRobot {


/* Message structure */

// general_msgs/geometry_msgs/pose2d_msg


/* Order structure */

// general_odrs/empty_odrs/empty_odr


/* device class */

class DeadReckoning: public device<pose2d_msg, empty_odr> {
public:
	/* Pointers of child device */
	device<twist_msg, empty_odr> *kinematics;

protected:
	/* Override: Called back after be shared an order */
	void odrCallback(empty_odr odr){
	}

	/* Override: Update myself */
	void selfTickerUpdate(ticker_args targs){
		float period = (float)targs.period_ms * 0.0010;

		twist_msg msg;

		msg = kinematics->shareMsg();

		float sin_theta = sinf(myMsg.theta + msg.omega * period/2.0);
		float cos_theta = cosf(myMsg.theta + msg.omega * period/2.0);

		float dx = msg.vx * period * cos_theta - msg.vy * period * sin_theta;
		float dy = msg.vx * period * sin_theta + msg.vy * period * cos_theta;

		kahanSummation(&myMsg.x, &c_x, dx);
		kahanSummation(&myMsg.y, &c_y, dy);
		kahanSummation(&myMsg.theta, &c_theta, msg.omega * period);
	}

	/* Override: Initialize */
	void initialize(){
		myMsg.x = 0.0f;
		myMsg.y = 0.0f;
		myMsg.theta = 0.0f;

		c_x = 0.0f;
		c_y = 0.0f;
		c_theta = 0.0f;
	}

	/* Personal private variables */
	float c_x, c_y, c_theta;

	/* Personal private functions */
	void kahanSummation(float*, float*,float);

public:
	/* Constructor */
	DeadReckoning(){
	}
};


} /* namespace dRobot */

#endif /* DEADRECKONING_H_ */
