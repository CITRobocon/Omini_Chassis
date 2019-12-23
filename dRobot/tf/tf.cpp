/*
 * tf.cpp
 *
 *  Created on: 2019/12/09
 *      Author: shohei
 */

#include "tf.h"

namespace dRobot {

tf::tf() : position(),
		   posture(1.0f, 0.0f, 0.0f,
				   0.0f, 1.0f, 0.0f,
			       0.0f, 0.0f, 1.0f){
}

tf tf::operator*(tf p){
	tf result;

	result.position = posture*p.position + position;
	result.posture = posture*p.posture;

	return result;
}

tf tf::operator*=(tf p){
	tf tmp;

	tmp.position = posture*p.position + position;
	tmp.posture = posture*p.posture;

	position = tmp.position;
	posture = tmp.posture;

	return *this;
}

tf tf::transform(tf p){
	tf tmp;

	tmp.position = p.posture*position + p.position;
	tmp.posture = p.posture*posture;

	position = tmp.position;
	posture = tmp.posture;

	return *this;
}

tf tf::translate(float x, float y, float z){
	vec3d v(x, y, z);

	position += v;

	return *this;
}

tf tf::translate(vec3d v){
	position += v;

	return *this;
}

tf tf::rotate_x(float theta){
	mat3x3 m(1.0f, 0.0f,        0.0f,
		     0.0f, cos(theta), -sin(theta),
	         0.0f, sin(theta),  cos(theta));

	posture = m * posture;

	return *this;
}

tf tf::rotate_y(float theta){
	mat3x3 m( cos(theta), 0.0f, sin(theta),
		      0.0f,       1.0f, 0.0f,
	         -sin(theta), 0.0f, cos(theta));

	posture = m * posture;

	return *this;
}

tf tf::rotate_z(float theta){
	mat3x3 m(cos(theta), -sin(theta), 0.0f,
		     sin(theta),  cos(theta), 0.0f,
	         0.0f,        0.0f,       1.0f);

	posture = m * posture;

	return *this;
}

} /* namespace dRobot */
