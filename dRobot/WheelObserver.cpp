
#include "WheelObserver.h"

namespace dRobot {


/* PRIVATE */

/* Personal private functions */

float WheelObserver::calcInvKinematics(tf wheel_pose, float vx, float vy, float omega){
	vec3d translation = asVec3d(vx, vy, 0.0f);
	vec3d rotation = asVec3d(0.0f, 0.0f, omega);
	vec3d unit = columnVec(wheel_pose.posture, 0);

	float vel = dot(translation + cross(rotation, wheel_pose.position), unit);

	return vel;
}


} /* namespace dRobot */
