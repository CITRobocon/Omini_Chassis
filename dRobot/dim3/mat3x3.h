/*
 * mat3x3.h
 *
 *  Created on: 2019/12/09
 *      Author: shohei
 */

#ifndef DIM3_MAT3X3_H_
#define DIM3_MAT3X3_H_

namespace dRobot {

class mat3x3 {
public:
	float element[3][3];

	mat3x3();

	mat3x3(float, float, float,
		   float, float, float,
		   float, float, float);

	// access to an element
	float operator()(int, int);

	// sigle operation
	mat3x3 operator-();

	// matrix-matrix operations
	//mat3x3 operator=(mat3x3);

	mat3x3 operator+=(mat3x3);
	mat3x3 operator-=(mat3x3);
	mat3x3 operator*=(mat3x3);

	mat3x3 operator+(mat3x3);
	mat3x3 operator-(mat3x3);
	mat3x3 operator*(mat3x3);

	// vector-scalar operations
	mat3x3 operator=(float);

	mat3x3 operator+=(float);
	mat3x3 operator-=(float);
	mat3x3 operator*=(float);
	mat3x3 operator/=(float);

	mat3x3 operator+(float);
	mat3x3 operator-(float);
	mat3x3 operator*(float);
	mat3x3 operator/(float);

	// set
	mat3x3 set(float, float, float,
			   float, float, float,
			   float, float, float);

	// friend functions
	friend mat3x3 transpose(mat3x3);
	friend mat3x3 inverse(mat3x3);
};

// matrix operations
mat3x3 asMat3x3(float, float, float,
		        float, float, float,
				float, float, float);
mat3x3 asMat3x3(float*);
mat3x3 transpose(mat3x3);
mat3x3 inverse(mat3x3);

} /* namespace dRobot */

#endif /* DIM3_MAT3X3_H_ */
