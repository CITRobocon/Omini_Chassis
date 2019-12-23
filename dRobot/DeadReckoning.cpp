
#include "DeadReckoning.h"

namespace dRobot {


void DeadReckoning::kahanSummation(float *sum, float *c, float x){
	// Kahan summation algorithm
	float y = x - *c;
	float t = *sum + x;
	*c = (t - *sum) - y;
	*sum = t;
}


} /* namespace dRobot */
