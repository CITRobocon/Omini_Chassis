/*
 * tf.h
 *
 *  Created on: 2019/12/09
 *      Author: shohei
 */

#ifndef TF_TF_H_
#define TF_TF_H_

#include "../dim3/dim3.h"

namespace dRobot {

class tf{
public:
	vec3d position;
	mat3x3 posture;

	// initialize position and posture with zero vector and identity matrix
	tf();

	// operators
	tf operator=(tf);

	tf operator*=(tf);

	tf operator*(tf);

	// functions
	tf transform(tf);

	tf translate(float, float, float);

	tf translate(vec3d);

	tf rotate_x(float);

	tf rotate_y(float);

	tf rotate_z(float);
};

} /* namespace dRobot */

#endif /* TF_TF_H_ */
