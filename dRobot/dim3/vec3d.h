/*
 * vec3d.h
 *
 *  Created on: 2019/12/09
 *      Author: shohei
 */

#ifndef DIM3_VEC3D_H_
#define DIM3_VEC3D_H_

#include <cmath>
#include <limits>

namespace dRobot {

class vec3d {
public:
	float component[3];

	vec3d();

	vec3d(float, float, float);

	// access to a component
	float operator()(int);

	// single operation
	vec3d operator-();

	// vector-vector operations
	vec3d operator=(vec3d);

	vec3d operator+=(vec3d);
	vec3d operator-=(vec3d);

	vec3d operator+(vec3d);
	vec3d operator-(vec3d);

	// vector-scalar operations
	vec3d operator=(float);

	vec3d operator+=(float);
	vec3d operator-=(float);
	vec3d operator*=(float);
	vec3d operator/=(float);

	vec3d operator+(float);
	vec3d operator-(float);
	vec3d operator*(float);
	vec3d operator/(float);

	// set
	void set(float, float, float);

	// friend functions
	friend float norm(vec3d);
	friend float dot(vec3d, vec3d);
	friend vec3d cross(vec3d, vec3d);
	friend vec3d normalize(vec3d);

	// friend global operators
	friend vec3d operator+(float, vec3d);
	friend vec3d operator-(float, vec3d);
	friend vec3d operator*(float, vec3d);
	friend vec3d operator/(float, vec3d);
};

// vector operations
vec3d asVec3d(float, float, float);
vec3d asVec3d(float*);
float norm(vec3d);
float dot(vec3d, vec3d);
vec3d cross(vec3d, vec3d);
vec3d normalize(vec3d);

// global operators
vec3d operator+(float, vec3d);
vec3d operator-(float, vec3d);
vec3d operator*(float, vec3d);
vec3d operator/(float, vec3d);

} /* namespace dRobot */

#endif /* DIM3_VEC3D_H_ */
