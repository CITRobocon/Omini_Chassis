/*
 * dim3.cpp
 *
 *  Created on: 2019/12/09
 *      Author: shohei
 */

#include "dim3.h"

namespace dRobot {

vec3d operator*(mat3x3 m, vec3d v){
	return asVec3d(m(0,0)*v(0) + m(0,1)*v(1) + m(0,2)*v(2),
   			        m(1,0)*v(0) + m(1,1)*v(1) + m(1,2)*v(2),
				     m(2,0)*v(0) + m(2,1)*v(1) + m(2,2)*v(2));
}

vec3d dot(mat3x3 m, vec3d v){
	return asVec3d(m(0,0)*v(0) + m(0,1)*v(1) + m(0,2)*v(2),
   			        m(1,0)*v(0) + m(1,1)*v(1) + m(1,2)*v(2),
				     m(2,0)*v(0) + m(2,1)*v(1) + m(2,2)*v(2));
}

vec3d solve(mat3x3 m, vec3d v){
	float det;

	det = (m(0,0) * (m(1,1)*m(2,2) - m(1,2)*m(2,1)) +
			m(0,1) * (m(1,2)*m(2,0) - m(1,0)*m(2,2)) +
  			 m(0,2) * (m(1,0)*m(2,1) - m(1,1)*m(2,0)));

	if (det < 0.00001){
		return asVec3d(0.0f, 0.0f, 0.0f);
	}

	float x[3];

	x[0] = ((m(1,1)*m(2,2) - m(1,2)*m(2,1)) * v(0) +
			 (m(1,2)*m(2,0) - m(1,0)*m(2,2)) * v(1) +
			  (m(1,0)*m(2,1) - m(1,1)*m(2,0)) * v(2)) / det;

	x[1] = ((m(2,1)*m(0,2) - m(2,2)*m(0,1)) * v(0) +
			 (m(2,2)*m(0,0) - m(2,0)*m(0,2)) * v(1) +
			  (m(2,0)*m(0,1) - m(2,1)*m(0,0)) * v(2)) / det;

	x[2] = ((m(0,1)*m(1,2) - m(0,2)*m(1,1)) * v(0) +
			 (m(0,2)*m(1,0) - m(0,0)*m(1,2)) * v(1) +
			  (m(0,0)*m(1,1) - m(0,1)*m(1,0)) * v(2)) / det;

	return asVec3d(x);
}

vec3d lineVec(mat3x3 m, int n){
	if (n < 0 || n > 3)
		return asVec3d(0.0f, 0.0f, 0.0f);

	return asVec3d(m(n,0), m(n,1), m(n,2));
}

vec3d columnVec(mat3x3 m, int n){
	if (n < 0 || n > 3)
		return asVec3d(0.0f, 0.0f, 0.0f);

	return asVec3d(m(0,n), m(1,n), m(2,n));
}

} // namespace dRobot
