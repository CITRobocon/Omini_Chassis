
#ifndef GENERAL_ODRS_GEOMETRY_ODRS_H_
#define GENERAL_ODRS_GEOMETRY_ODRS_H_

#include "../tf/tf.h"


namespace dRobot{


typedef struct{
	tf pose;
}pose3d_odr;


typedef struct{
	float x;
	float y;
	float theta;
} pose2d_odr;


typedef struct{
	float vx;
	float vy;
	float omega;
} twist_odr;


}; // namespace dRobot

#endif /* GENERAL_MSGS_GEOMETRY_MSGS_H_ */
