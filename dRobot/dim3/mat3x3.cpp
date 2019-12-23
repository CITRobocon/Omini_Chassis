/*
 * mat3x3.cpp
 *
 *  Created on: 2019/12/09
 *      Author: shohei
 */

#include "mat3x3.h"

namespace dRobot {

mat3x3::mat3x3() {
	element[0][0] = 0.0f;
	element[0][1] = 0.0f;
	element[0][2] = 0.0f;

	element[1][0] = 0.0f;
	element[1][1] = 0.0f;
	element[1][2] = 0.0f;

	element[2][0] = 0.0f;
	element[2][1] = 0.0f;
	element[2][2] = 0.0f;
}

mat3x3::mat3x3(float e00, float e01, float e02,
			   float e10, float e11, float e12,
			   float e20, float e21, float e22) {
	element[0][0] = e00;
	element[0][1] = e01;
	element[0][2] = e02;

	element[1][0] = e10;
	element[1][1] = e11;
	element[1][2] = e12;

	element[2][0] = e20;
	element[2][1] = e21;
	element[2][2] = e22;
}

//access to an element
float mat3x3::operator()(int i, int j){
	return element[i][j];
}

// single operation
mat3x3 mat3x3::operator-(){
	mat3x3 result;

	result.element[0][0] = -element[0][0];
	result.element[0][1] = -element[0][1];
	result.element[0][2] = -element[0][2];

	result.element[1][0] = -element[1][0];
	result.element[1][1] = -element[1][1];
	result.element[1][2] = -element[1][2];

	result.element[2][0] = -element[2][0];
	result.element[2][1] = -element[2][1];
	result.element[2][2] = -element[2][2];

	return result;
}

// matrix-matrix operations
mat3x3 mat3x3::operator+=(mat3x3 m){
	element[0][0] += m.element[0][0];
	element[0][1] += m.element[0][1];
	element[0][2] += m.element[0][2];

	element[1][0] += m.element[1][0];
	element[1][1] += m.element[1][1];
	element[1][2] += m.element[1][2];

	element[2][0] += m.element[2][0];
	element[2][1] += m.element[2][1];
	element[2][2] += m.element[2][2];

	return *this;
}

mat3x3 mat3x3::operator-=(mat3x3 m){
	element[0][0] -= m.element[0][0];
	element[0][1] -= m.element[0][1];
	element[0][2] -= m.element[0][2];

	element[1][0] -= m.element[1][0];
	element[1][1] -= m.element[1][1];
	element[1][2] -= m.element[1][2];

	element[2][0] -= m.element[2][0];
	element[2][1] -= m.element[2][1];
	element[2][2] -= m.element[2][2];

	return *this;
}

mat3x3 mat3x3::operator*=(mat3x3 m){
	mat3x3 tmp;

	tmp.element[0][0] = (element[0][0] * m.element[0][0] +
			              element[0][1] * m.element[1][0] +
			               element[0][2] * m.element[2][0]);

	tmp.element[0][1] = (element[0][0] * m.element[0][1] +
			              element[0][1] * m.element[1][1] +
			               element[0][2] * m.element[2][1]);

	tmp.element[0][2] = (element[0][0] * m.element[0][2] +
			              element[0][1] * m.element[1][2] +
			               element[0][2] * m.element[2][2]);

	tmp.element[1][0] = (element[1][0] * m.element[0][0] +
			              element[1][1] * m.element[1][0] +
			               element[1][2] * m.element[2][0]);

	tmp.element[1][1] = (element[1][0] * m.element[0][1] +
			              element[1][1] * m.element[1][1] +
			               element[1][2] * m.element[2][1]);

	tmp.element[1][2] = (element[1][0] * m.element[0][2] +
			              element[1][1] * m.element[1][2] +
			               element[1][2] * m.element[2][2]);

	tmp.element[2][0] = (element[2][0] * m.element[0][0] +
			              element[2][1] * m.element[1][0] +
			               element[2][2] * m.element[2][0]);

	tmp.element[2][1] = (element[2][0] * m.element[0][1] +
			              element[2][1] * m.element[1][1] +
			               element[2][2] * m.element[2][1]);

	tmp.element[2][2] = (element[2][0] * m.element[0][2] +
			              element[2][1] * m.element[1][2] +
			               element[2][2] * m.element[2][2]);

	element[0][0] = tmp.element[0][0];
	element[0][1] = tmp.element[0][1];
	element[0][2] = tmp.element[0][2];

	element[1][0] = tmp.element[1][0];
	element[1][1] = tmp.element[1][1];
	element[1][2] = tmp.element[1][2];

	element[2][0] = tmp.element[2][0];
	element[2][1] = tmp.element[2][1];
	element[2][2] = tmp.element[2][2];

	return *this;
}

mat3x3 mat3x3::operator+(mat3x3 m){
	mat3x3 result;

	result.element[0][0] = element[0][0] + m.element[0][0];
	result.element[0][1] = element[0][1] + m.element[0][1];
	result.element[0][2] = element[0][2] + m.element[0][2];

	result.element[1][0] = element[1][0] + m.element[1][0];
	result.element[1][1] = element[1][1] + m.element[1][1];
	result.element[1][2] = element[1][2] + m.element[1][2];

	result.element[2][0] = element[2][0] + m.element[2][0];
	result.element[2][1] = element[2][1] + m.element[2][1];
	result.element[2][2] = element[2][2] + m.element[2][2];

	return result;
}

mat3x3 mat3x3::operator-(mat3x3 m){
	mat3x3 result;

	result.element[0][0] = element[0][0] - m.element[0][0];
	result.element[0][1] = element[0][1] - m.element[0][1];
	result.element[0][2] = element[0][2] - m.element[0][2];

	result.element[1][0] = element[1][0] - m.element[1][0];
	result.element[1][1] = element[1][1] - m.element[1][1];
	result.element[1][2] = element[1][2] - m.element[1][2];

	result.element[2][0] = element[2][0] - m.element[2][0];
	result.element[2][1] = element[2][1] - m.element[2][1];
	result.element[2][2] = element[2][2] - m.element[2][2];

	return result;
}

mat3x3 mat3x3::operator*(mat3x3 m){
	mat3x3 result;

	result.element[0][0] = (element[0][0] * m.element[0][0] +
			              element[0][1] * m.element[1][0] +
			               element[0][2] * m.element[2][0]);

	result.element[0][1] = (element[0][0] * m.element[0][1] +
			              element[0][1] * m.element[1][1] +
			               element[0][2] * m.element[2][1]);

	result.element[0][2] = (element[0][0] * m.element[0][2] +
			              element[0][1] * m.element[1][2] +
			               element[0][2] * m.element[2][2]);

	result.element[1][0] = (element[1][0] * m.element[0][0] +
			              element[1][1] * m.element[1][0] +
			               element[1][2] * m.element[2][0]);

	result.element[1][1] = (element[1][0] * m.element[0][1] +
			              element[1][1] * m.element[1][1] +
			               element[1][2] * m.element[2][1]);

	result.element[1][2] = (element[1][0] * m.element[0][2] +
			              element[1][1] * m.element[1][2] +
			               element[1][2] * m.element[2][2]);

	result.element[2][0] = (element[2][0] * m.element[0][0] +
			              element[2][1] * m.element[1][0] +
			               element[2][2] * m.element[2][0]);

	result.element[2][1] = (element[2][0] * m.element[0][1] +
			              element[2][1] * m.element[1][1] +
			               element[2][2] * m.element[2][1]);

	result.element[2][2] = (element[2][0] * m.element[0][2] +
			              element[2][1] * m.element[1][2] +
			               element[2][2] * m.element[2][2]);

	return result;
}

// matrix-scalar operation
mat3x3 mat3x3::operator=(float s){
	element[0][0] = s;
	element[0][1] = s;
	element[0][2] = s;

	element[1][0] = s;
	element[1][1] = s;
	element[1][2] = s;

	element[2][0] = s;
	element[2][1] = s;
	element[2][2] = s;

	return *this;
}

mat3x3 mat3x3::operator+=(float s){
	element[0][0] += s;
	element[0][1] += s;
	element[0][2] += s;

	element[1][0] += s;
	element[1][1] += s;
	element[1][2] += s;

	element[2][0] += s;
	element[2][1] += s;
	element[2][2] += s;

	return *this;
}

mat3x3 mat3x3::operator-=(float s){
	element[0][0] -= s;
	element[0][1] -= s;
	element[0][2] -= s;

	element[1][0] -= s;
	element[1][1] -= s;
	element[1][2] -= s;

	element[2][0] -= s;
	element[2][1] -= s;
	element[2][2] -= s;

	return *this;
}

mat3x3 mat3x3::operator*=(float s){
	element[0][0] *= s;
	element[0][1] *= s;
	element[0][2] *= s;

	element[1][0] *= s;
	element[1][1] *= s;
	element[1][2] *= s;

	element[2][0] *= s;
	element[2][1] *= s;
	element[2][2] *= s;

	return *this;
}

mat3x3 mat3x3::operator/=(float s){
	element[0][0] /= s;
	element[0][1] /= s;
	element[0][2] /= s;

	element[1][0] /= s;
	element[1][1] /= s;
	element[1][2] /= s;

	element[2][0] /= s;
	element[2][1] /= s;
	element[2][2] /= s;

	return *this;
}

mat3x3 mat3x3::operator+(float s){
	mat3x3 result;

	result.element[0][0] = element[0][0] + s;
	result.element[0][1] = element[0][1] + s;
	result.element[0][2] = element[0][2] + s;

	result.element[1][0] = element[1][0] + s;
	result.element[1][1] = element[1][1] + s;
	result.element[1][2] = element[1][2] + s;

	result.element[2][0] = element[2][0] + s;
	result.element[2][1] = element[2][1] + s;
	result.element[2][2] = element[2][2] + s;

	return result;
}

mat3x3 mat3x3::operator-(float s){
	mat3x3 result;

	result.element[0][0] = element[0][0] - s;
	result.element[0][1] = element[0][1] - s;
	result.element[0][2] = element[0][2] - s;

	result.element[1][0] = element[1][0] - s;
	result.element[1][1] = element[1][1] - s;
	result.element[1][2] = element[1][2] - s;

	result.element[2][0] = element[2][0] - s;
	result.element[2][1] = element[2][1] - s;
	result.element[2][2] = element[2][2] - s;

	return result;
}

mat3x3 mat3x3::operator*(float s){
	mat3x3 result;

	result.element[0][0] = element[0][0] * s;
	result.element[0][1] = element[0][1] * s;
	result.element[0][2] = element[0][2] * s;

	result.element[1][0] = element[1][0] * s;
	result.element[1][1] = element[1][1] * s;
	result.element[1][2] = element[1][2] * s;

	result.element[2][0] = element[2][0] * s;
	result.element[2][1] = element[2][1] * s;
	result.element[2][2] = element[2][2] * s;

	return result;
}

mat3x3 mat3x3::operator/(float s){
	mat3x3 result;

	result.element[0][0] = element[0][0] / s;
	result.element[0][1] = element[0][1] / s;
	result.element[0][2] = element[0][2] / s;

	result.element[1][0] = element[1][0] / s;
	result.element[1][1] = element[1][1] / s;
	result.element[1][2] = element[1][2] / s;

	result.element[2][0] = element[2][0] / s;
	result.element[2][1] = element[2][1] / s;
	result.element[2][2] = element[2][2] / s;

	return result;
}

// set
mat3x3 mat3x3::set(float e00, float e01, float e02,
                   float e10, float e11, float e12,
	               float e20, float e21, float e22){
	element[0][0] = e00;
	element[0][1] = e01;
	element[0][2] = e02;

	element[1][0] = e10;
	element[1][1] = e11;
	element[1][2] = e12;

	element[2][0] = e20;
	element[2][1] = e21;
	element[2][2] = e22;

	return *this;
}


// matrix operations
mat3x3 asMat3x3(float e00, float e01, float e02,
		        float e10, float e11, float e12,
				float e20, float e21, float e22){
	mat3x3 result;

	result.set(e00, e01, e02,
			   e10, e11, e12,
			   e20, e21, e22);

	return result;
}

mat3x3 asMat3x3(float e[3][3]){
	mat3x3 result;

	result.set(e[0][0], e[0][1], e[0][2],
			   e[1][0], e[1][1], e[1][2],
			   e[2][0], e[2][1], e[2][2]);

	return result;
}


mat3x3 asMat3x3(float*);

mat3x3 transpose(mat3x3 m){
	mat3x3 result;

	result.element[0][0] = m.element[0][0];
	result.element[0][1] = m.element[1][0];
	result.element[0][2] = m.element[2][0];

	result.element[1][0] = m.element[0][1];
	result.element[1][1] = m.element[1][1];
	result.element[1][2] = m.element[2][1];

	result.element[2][0] = m.element[0][2];
	result.element[2][1] = m.element[1][2];
	result.element[2][2] = m.element[2][2];

	return result;
}

mat3x3 inverse(mat3x3 m){
	float det;

	det = (m.element[0][0] * (m.element[1][1]*m.element[2][2] - m.element[1][2]*m.element[2][1]) +
			m.element[0][1] * (m.element[1][2]*m.element[2][0] - m.element[1][0]*m.element[2][2]) +
			 m.element[0][2] * (m.element[1][0]*m.element[2][1] - m.element[1][1]*m.element[2][0]));

	if (det < 0.00001 && det > -0.00001){
		return asMat3x3(0.0f, 0.0f, 0.0f,
				        0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f);
	}

	float tmp[3][3];

	tmp[0][0] = (m.element[1][1]*m.element[2][2] - m.element[1][2]*m.element[2][1]) / det;
	tmp[1][0] = (m.element[1][2]*m.element[2][0] - m.element[1][0]*m.element[2][2]) / det;
	tmp[2][0] = (m.element[1][0]*m.element[2][1] - m.element[1][1]*m.element[2][0]) / det;

	tmp[0][1] = (m.element[2][1]*m.element[0][2] - m.element[2][2]*m.element[0][1]) / det;
	tmp[1][1] = (m.element[2][2]*m.element[0][0] - m.element[2][0]*m.element[0][2]) / det;
	tmp[2][1] = (m.element[2][0]*m.element[0][1] - m.element[2][1]*m.element[0][0]) / det;

	tmp[0][2] = (m.element[0][1]*m.element[1][2] - m.element[0][2]*m.element[1][1]) / det;
	tmp[1][2] = (m.element[0][2]*m.element[1][0] - m.element[0][0]*m.element[1][2]) / det;
	tmp[2][2] = (m.element[0][0]*m.element[1][1] - m.element[0][1]*m.element[1][0]) / det;

	return asMat3x3(tmp);
}

} /* namespace dRobot */
