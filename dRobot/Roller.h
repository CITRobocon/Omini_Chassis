/*
 * Roller.h
 *
 *  Created on: 2019/12/09
 *      Author: shohei
 */

#ifndef ROLLER_H_
#define ROLLER_H_

/*
 *   Name: Roller
 *   About: A Roller pushed by fixed point
 *
 *   Upward output: Angular velocity of wheel calculated on downward input
 *   Upward input:	2D translation velocity and z-axis angular velocity
 *
 *   Downward output: Angular velocity of wheel calculated on upward input
 *   Downward input:  2D translation velocity and z-axis angular velocity
 *
 *                __________
 *     twist --> |          | --> Roller/float
 *               |  Roller  |
 *     float <-- |__________| <-- Roller/twist
 *
 */


#include <cstdint>
#include "common_includes.h"

#include "device.h"
#include "general_msgs/empty_msgs.h"
#include "general_msgs/numeric_msgs.h"
#include "general_msgs/geometry_msgs.h"
#include "general_odrs/empty_odrs.h"
#include "general_odrs/numeric_odrs.h"
#include "general_odrs/geometry_odrs.h"

namespace dRobot {


/* Message structure */

// general_msgs/numeric_msgs/float_msg


/* Order structure */

// general_msgs/geometry_odrs/twist_msg


/* device class */

class Roller: public device<float_msg, twist_odr> {
	/* Pointers of child device */
	//device<DeadReckoning_msg, DeadReckoning_odr> *deadreckoning;
	device<twist_msg, float_odr> *dev;

	/* Override: Called back before share a message */
	void msgCallback(float_msg msg){
		twist_msg dmsg;

		dmsg = dev->shareMsg();

		// Solve kinematics
		myMsg.val = getWheelAngVel(dmsg.vx, dmsg.vy, dmsg.omega);
	}

	/* Override: Called back after be shared an order */
	void odrCallback(twist_odr odr){
		float_odr dodr;

		// Solve kinematics
		dodr.val = getWheelAngVel(odr.vx, odr.vy, odr.omega);

		dev->shareOdr(dodr);
	}

	/* Personal private variables */
	float wheel_radius;

	/* Personal private functions */
	float getWheelAngVel(float, float, float);

public:
	/* Constructor */
	Roller(float radius){
		wheel_radius = radius;
	}
};


} /* namespace dRobot */

#endif /* ROLLER_H_ */
