
#include "MotorDriver.h"

namespace dRobot {


/* PRIVATE */

/* Personal private functions */
float MotorDriver::saturation(float val){
	if (val < -max_in){
		return -max_in;
	}else if (val > max_in){
		return max_in;
	}

	return val;
}

uint32_t MotorDriver::convertTimCCR(float duty){
	return static_cast<uint32_t>(fabs(duty) * (pwm_max - pwm_min) + pwm_min);
}

} /* namespace dRobot */
