
#ifndef POSEPOINT_H_
#define POSEPOINT_H_

/*
 *   Name: PosePoint
 *   About: A PosePoint light
 *
 *   Upward output: None
 *   Upward input:  0: down, 1: light
 *
 *   Downward output: World
 *   Downward input:  None
 *                _____________
 *      None --> |             | --> PosePoint/empty
 *               |  PosePoint  |
 *     World <-- |_____________| <-- PosePoint/uint8
 *
 */


#include <cstdint>
#include "common_includes.h"

#include "device.h"
#include "general_msgs/empty_msgs.h"
#include "general_odrs/empty_odrs.h"


namespace dRobot {


/* Message structure */

// common_msgs/empty_msgs/empty_msg


/* Order structure */

// common_odrs/numeric_odrs/uint8_odr


/* device class */

class PosePoint: public device<empty_msg, empty_odr> {
	/* Pointers of child device */
	// None

	/* Override: Called back before share a message */
	void msgCallback(empty_msg msg){
	}

	/* Override: Called back after be shared an order */
	void odrCallback(empty_odr odr){
	}

	/* Personal private variables */

	/* Personal private functions */

public:
	/* Constructor */
	PosePoint(){
	}
};


} /* namespace dRobot */

#endif /* POSEPOINT_H_ */
