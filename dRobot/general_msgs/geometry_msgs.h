
#ifndef GENERAL_MSGS_GEOMETRY_MSGS_H_
#define GENERAL_MSGS_GEOMETRY_MSGS_H_

#include "../tf/tf.h"

namespace dRobot{


typedef struct{
	tf pose;
}pose3d_msg;


typedef struct{
	float x;
	float y;
	float theta;
} pose2d_msg;


typedef struct{
	float vx;
	float vy;
	float omega;
} twist_msg;


}; // namespace dRobot

#endif /* GENERAL_MSGS_GEOMETRY_MSGS_H_ */
