
#include "Odometer.h"

namespace dRobot {


/* PRIVATE */

/* Personal private functions */
float Odometer::getAndResetEncRotate(){
	// read count
	uint16_t cnt = enc_counter->CNT;

	// reset count
	enc_counter->CNT -= cnt;

	// convert unsigned count to signed pulses
	short pulses = (cnt>>15)?(-(short)(~cnt)-1):(cnt);

	// convert pulses to radius
	return 2.0 * M_PI * (float)(pulses) / enc_ppr;
}

float Odometer::getWheelDisplacement(){
	float rotate = getAndResetEncRotate();

	return wheel_radius*rotate;
}


} /* namespace dRobot */
