
#include "PIDController.h"

namespace dRobot {


/* PRIVATE */

/* Personal private functions */

void PIDController::updateErrors(float err, float period){
	e0 = ep;
	ep = err;
	ei = ep * period;
	ed = (e0 - ep) / period;
}

float PIDController::calcInput(){
	float input;

	if (i_gain * ei > i_limit){
		input = p_gain*ep + d_gain*ed + i_limit;
	}
	else{
		input = p_gain*ep + i_gain*ei + d_gain*ed;
	}

	input += shift_bias;

	if (input > 0.0){
		input += magnitude_bias;
	}
	else if (input < 0.0){
		input -= magnitude_bias;
	}

	return input;
}


} /* namespace dRobot */
