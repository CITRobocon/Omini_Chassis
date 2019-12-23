/*
 * vec3d.cpp
 *
 *  Created on: 2019/12/09
 *      Author: shohei
 */

#include "vec3d.h"

namespace dRobot {

vec3d::vec3d(){
	component[0] = 0.0f;
	component[1] = 0.0f;
	component[2] = 0.0f;
}

vec3d::vec3d(float c0, float c1, float c2){
	component[0] = c0;
	component[1] = c1;
	component[2] = c2;
}

float vec3d::operator()(int n){
	if(n < 0 || n > 2)
		return std::numeric_limits<float>::quiet_NaN();

	return component[n];
}

vec3d vec3d::operator-(){
	vec3d result;

	result.component[0] = -component[0];
	result.component[1] = -component[1];
	result.component[2] = -component[2];

	return result;
}

vec3d vec3d::operator=(vec3d v){
	component[0] = v.component[0];
	component[1] = v.component[1];
	component[2] = v.component[2];

	return *this;
}

vec3d vec3d::operator+=(vec3d v){
	component[0] += v.component[0];
	component[1] += v.component[1];
	component[2] += v.component[2];

	return *this;
}

vec3d vec3d::operator-=(vec3d v){
	component[0] -= v.component[0];
	component[1] -= v.component[1];
	component[2] -= v.component[2];

	return *this;
}

vec3d vec3d::operator+(vec3d v){
	vec3d result;

	result.component[0] = component[0] + v.component[0];
	result.component[1] = component[1] + v.component[1];
	result.component[2] = component[2] + v.component[2];

	return result;
}

vec3d vec3d::operator-(vec3d v){
	vec3d result;

	result.component[0] = component[0] - v.component[0];
	result.component[1] = component[1] - v.component[1];
	result.component[2] = component[2] - v.component[2];

	return result;
}

// vector and scalar operations
vec3d vec3d::operator=(float s){
	component[0] = s;
	component[1] = s;
	component[2] = s;

	return *this;
}

vec3d vec3d::operator+=(float s){
	component[0] += s;
	component[1] += s;
	component[2] += s;

	return *this;
}

vec3d vec3d::operator-=(float s){
	component[0] -= s;
	component[1] -= s;
	component[2] -= s;

	return *this;
}

vec3d vec3d::operator*=(float s){
	component[0] *= s;
	component[1] *= s;
	component[2] *= s;

	return *this;
}

vec3d vec3d::operator/=(float s){
	component[0] /= s;
	component[1] /= s;
	component[2] /= s;

	return *this;
}

vec3d vec3d::operator+(float s){
	vec3d result;

	result.component[0] = component[0] + s;
	result.component[1] = component[1] + s;
	result.component[2] = component[2] + s;

	return result;
}

vec3d vec3d::operator-(float s){
	vec3d result;

	result.component[0] = component[0] - s;
	result.component[1] = component[1] - s;
	result.component[2] = component[2] - s;

	return result;
}

vec3d vec3d::operator*(float s){
	vec3d result;

	result.component[0] = component[0] * s;
	result.component[1] = component[1] * s;
	result.component[2] = component[2] * s;

	return result;
}

vec3d vec3d::operator/(float s){
	vec3d result;

	result.component[0] = component[0] / s;
	result.component[1] = component[1] / s;
	result.component[2] = component[2] / s;

	return result;
}

void vec3d::set(float c0, float c1, float c2){
	component[0] = c0;
	component[1] = c1;
	component[2] = c2;
}


//~~~

vec3d asVec3d(float c0, float c1, float c2){
	vec3d result(c0, c1, c2);

	return result;
}

vec3d asVec3d(float c[3]){
	vec3d result(c[0], c[1], c[2]);

	return result;
}

float norm(vec3d v){
	return std::sqrt(v.component[0]*v.component[0] +
			          v.component[1]*v.component[1] +
					   v.component[2]*v.component[2]);
}

float dot(vec3d v1, vec3d v2){
	return (v1.component[0]*v2.component[0] +
			 v1.component[1]*v2.component[1] +
			  v1.component[2]*v2.component[2]);
}

vec3d cross(vec3d v1, vec3d v2){
	vec3d result;

	result.component[0] = (v1.component[1] * v2.component[2] -
							v1.component[2] * v2.component[1]);

	result.component[1] = (v1.component[2] * v2.component[0] -
							v1.component[0] * v2.component[2]);

	result.component[2] = (v1.component[0] * v2.component[1] -
							v1.component[1] * v2.component[0]);

	return result;
}

vec3d normalize(vec3d v){
	vec3d result;

	float norm = std::sqrt(v.component[0]*v.component[0] +
				            v.component[1]*v.component[1] +
					    	 v.component[2]*v.component[2]);

	result.component[0] = v.component[0] / norm;
	result.component[1] = v.component[1] / norm;
	result.component[2] = v.component[2] / norm;

	return result;
}

vec3d operator+(float s, vec3d v){
	vec3d result;

	result.component[0] = s + v.component[0];
	result.component[1] = s + v.component[1];
	result.component[2] = s + v.component[2];

	return result;
}

vec3d operator-(float s, vec3d v){
	vec3d result;

	result.component[0] = s - v.component[0];
	result.component[1] = s - v.component[1];
	result.component[2] = s - v.component[2];

	return result;
}

vec3d operator*(float s, vec3d v){
	vec3d result;

	result.component[0] = s * v.component[0];
	result.component[1] = s * v.component[1];
	result.component[2] = s * v.component[2];

	return result;
}

vec3d operator/(float s, vec3d v){
	vec3d result;

	result.component[0] = s / v.component[0];
	result.component[1] = s / v.component[1];
	result.component[2] = s / v.component[2];

	return result;
}

} /* namespace dRobot */
