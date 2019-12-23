/*
 * dim3.h
 *
 *  Created on: 2019/12/09
 *      Author: shohei
 */

#ifndef DIM3_DIM3_H_
#define DIM3_DIM3_H_

#include "vec3d.h"
#include "mat3x3.h"

namespace dRobot {

// matrix-vector operations
vec3d operator*(mat3x3, vec3d);

vec3d dot(mat3x3, vec3d);

vec3d solve(mat3x3, vec3d);

vec3d lineVec(mat3x3, int);

vec3d columnVec(mat3x3, int);

} //namespace dRobot

#endif /* DIM3_DIM3_H_ */
