
#ifndef WHEELOBSERVER_H_
#define WHEELOBSERVER_H_

/*
 *   Name: WheelObserver
 *   About: A PID-controller
 *
 *   Upward output: None
 *   Upward input:	Target value
 *
 *   Downward output: Input feedback
 *   Downward input:  Feedback value observing
 *
 *                ___________________
 *     float --> |                   | --> WheelObserver/empty
 *               |  WheelObserver  |
 *     float <-- |___________________| <-- WheelObserver/float
 *
 */


#include <cstdint>
#include "common_includes.h"

#include "device.h"
#include "PIDController.h"
#include "general_msgs/empty_msgs.h"
#include "general_msgs/numeric_msgs.h"
#include "general_msgs/geometry_msgs.h"
#include "general_odrs/empty_odrs.h"
#include "general_odrs/numeric_odrs.h"
#include "general_odrs/geometry_odrs.h"

namespace dRobot {


/* Message structure */

// common_msgs/empty_msgs/empty_msg


/* Order structure */

// common_odrs/numeric_odrs/float_odr


/* device class */

class WheelObserver: public device<empty_msg, twist_odr> {
public:
	/* Pointers of child device */
	device<twist_msg, empty_odr> *obs;
	device<empty_msg, float_odr> *err[4];
	device<empty_msg, empty_odr> *wheel[4];

protected:
	/* Override: Called back before share a message */
	void msgCallback(empty_msg msg){
	}

	/* Override: Called back after be shared an order */
	void odrCallback(twist_odr odr){
		for (int i = 0; i < 4; i++){
			if (wheel[i] != nullptr)
				target[i] = calcInvKinematics(wheel[i]->getRelativePose(), odr.vx, odr.vy, odr.omega);
		}
	}

	/* Override: Update myself */
	void selfTickerUpdate(ticker_args targs){
		twist_msg msg = obs->shareMsg();
		float_odr odr;

		for (int i = 0; i < 4; i++){
			if (wheel[i] != nullptr && err[i] != nullptr){
				odr.val = target[i] - calcInvKinematics(wheel[i]->getRelativePose(), msg.vx, msg.vy, msg.omega);
				err[i]->shareOdr(odr);
			}
		}
	}

	/* Override: Initialize */
	void initialize(){
	}

	/* Personal private variables */
	float target[4];

	/* Personal private functions */
	float calcInvKinematics(tf, float, float, float);

public:
	/* Constructor */
	WheelObserver(){
		obs = nullptr;
		for (int i = 0; i < 4; i++){
			wheel[i] = nullptr;
			err[i] = nullptr;
		}
	}
};


} /* namespace dRobot */

#endif /* WHEELOBSERVER_H_ */
