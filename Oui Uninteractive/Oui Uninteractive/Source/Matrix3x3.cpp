/**************************************************************************
* @file InputKeys.cpp
* @author
* @par DP email:
* @par Course: CSD 2401
* @par Software Engineering Project 3
* @date 09-05-2023
* @brief
*************************************************************************/
#include "Matrix3x3.h"
#include <math.h>

constexpr float PI = 3.14159265358f;

/**************************************************************************/
/*!
	Constructors
*/
/**************************************************************************/
Mtx33::Matrix3x3(const float* pArr)
{
	for (int i = 0; i < 9; ++i) {
		m[i] = pArr[i];
	}
}

Mtx33::Matrix3x3(float _00, float _01, float _02,
					float _10, float _11, float _12,
					float _20, float _21, float _22)
{
	m00 = _00;
	m01 = _01;
	m02 = _02;
	m10 = _10;
	m11 = _11;
	m12 = _12;
	m20 = _20;
	m21 = _21;
	m22 = _22;
}

/**************************************************************************/
/*!
	Copy assignment
*/
/**************************************************************************/
Mtx33& Mtx33::operator=(const Mtx33& rhs)
{
	// Iterate through rhs.m
	for (int i = 0; i < 9; ++i) {
		m[i] = rhs.m[i];
	}

	return *this;
}

/**************************************************************************/
/*!
	Cross product 2 matrices and save the resultant matrix in the 
	current matrix
*/
/**************************************************************************/
Mtx33& Mtx33::operator*=(const Mtx33& rhs)
{
	// Cross product *this and rhs
	Mtx33 temp;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k)
			{
				temp.m2[i][j] += m2[i][k] * rhs.m2[k][j];
			}
		}
	}
		
	// Assign the resultant matrix to *this
	*this = temp;

	return *this;
}

/**************************************************************************/
/*!
	This function returns the result of the cross product of 2 matrices
*/
/**************************************************************************/
Mtx33 operator*(const Mtx33& lhs, const Mtx33& rhs)
{
	// Cross product *this and rhs
	Mtx33 temp;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k)
			{
				temp.m2[i][j] += lhs.m2[i][k] * rhs.m2[k][j];
			}
		}
	}

	return temp;
}

/**************************************************************************/
/*!
	This operator multiplies the matrix pMtx with the vector rhs
	and returns the result as a vector
	*/
	/**************************************************************************/
Vector2D operator * (const Mtx33& pMtx, const Vec2& rhs)
{
	// Assign vector rhs to a temporary matrix
	Mtx33 temp_m;
	temp_m.m00 = rhs.x;
	temp_m.m10 = rhs.y;
	temp_m.m20 = 1;

	// Cross product the 2 matrices and 
	// assign m00 and m10 to a temporary vector
	Vec2 temp_v;
	temp_v.x = (pMtx * temp_m).m00;
	temp_v.y = (pMtx * temp_m).m10;

	return temp_v;
}

/**************************************************************************/
/*!
	This function sets the matrix pResult to the identity matrix
	*/
	/**************************************************************************/
void Mtx33Identity(Mtx33& pResult)
{
	/*
		1	0	0
		0	1	0
		0	0	1
	*/

	Mtx33 temp;
	temp.m00 = 1;
	temp.m11 = 1;
	temp.m22 = 1;

	pResult = temp;
}

/**************************************************************************/
/*!
	This function creates a translation matrix from x & y
	and saves it in pResult
	*/
	/**************************************************************************/
void Mtx33Translate(Mtx33& pResult, float x, float y)
{
	/*
		1	0	x
		0	1	y
		0	0	1
	*/

	Mtx33Identity(pResult);
	pResult.m02 = x;
	pResult.m12 = y;
}

/**************************************************************************/
/*!
	This function creates a scaling matrix from x & y
	and saves it in pResult
	*/
	/**************************************************************************/
void Mtx33Scale(Mtx33& pResult, float x, float y)
{
	/*
		x	0	0
		0	y	0
		0	0	1
	*/

	Mtx33Identity(pResult);
	pResult.m00 = x;
	pResult.m11 = y;
}

/**************************************************************************/
/*!
	This matrix creates a rotation matrix from "angle" whose value
	is in radian. Save the resultant matrix in pResult.
	*/
	/**************************************************************************/
void Mtx33RotRad(Mtx33& pResult, float angle)
{
	/*
		cos a	-sin a	 0
		sin a	 cos a	 0
		0		 0		 1
	*/

	Mtx33Identity(pResult);
	pResult.m00 =  cosf(angle);
	pResult.m01 = -sinf(angle);
	pResult.m10 =  sinf(angle);
	pResult.m11 =  cosf(angle);
}

/**************************************************************************/
/*!
	This matrix creates a rotation matrix from "angle" whose value
	is in degree. Save the resultant matrix in pResult.
	*/
	/**************************************************************************/
void Mtx33RotDeg(Mtx33& pResult, float angle)
{
	/*
		cos a	-sin a	 0
		sin a	 cos a	 0
		0		 0		 1
	*/

	Mtx33Identity(pResult);
	pResult.m00 =  cosf(PI / 180.0f * angle);
	pResult.m01 = -sinf(PI / 180.0f * angle);
	pResult.m10 =  sinf(PI / 180.0f * angle);
	pResult.m11 =  cosf(PI / 180.0f * angle);
}

/**************************************************************************/
/*!
	This functions calculated the transpose matrix of pMtx
	and saves it in pResult
	*/
	/**************************************************************************/
void Mtx33Transpose(Mtx33& pResult, const Mtx33& pMtx)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			pResult.m2[j][i] = pMtx.m2[i][j];
		}
	}
}

/**************************************************************************/
/*!
	This function calculates the inverse matrix of pMtx and saves the
	result in pResult. If the matrix inversion fails, pResult
	would be set to NULL.
*/
/**************************************************************************/
void Mtx33Inverse(Mtx33* pResult, float* determinant, const Mtx33& pMtx)
{
	// Calculate the determinant
	*determinant = (pMtx.m00 * pMtx.m11 * pMtx.m22) + 
		(pMtx.m01 * pMtx.m12 * pMtx.m20) + 
		(pMtx.m10 * pMtx.m21 * pMtx.m02) - 
		(pMtx.m02 * pMtx.m11 * pMtx.m20) - 
		(pMtx.m01 * pMtx.m10 * pMtx.m22) - 
		(pMtx.m12 * pMtx.m21 * pMtx.m00);

	// Set pResult to nullptr if the determinant is 0
	if (*determinant == 0)
		pResult = nullptr;

	else {
		// Calculate adjoint of matrix (before transposing)
		Mtx33 adjoint;
		adjoint.m00 = (pMtx.m11 * pMtx.m22 - pMtx.m12 * pMtx.m21);
		adjoint.m01 = -(pMtx.m10 * pMtx.m22 - pMtx.m12 * pMtx.m20);
		adjoint.m02 = (pMtx.m10 * pMtx.m21 - pMtx.m11 * pMtx.m20);
		adjoint.m10 = -(pMtx.m01 * pMtx.m22 - pMtx.m02 * pMtx.m21);
		adjoint.m11 = (pMtx.m00 * pMtx.m22 - pMtx.m02 * pMtx.m20);
		adjoint.m12 = -(pMtx.m00 * pMtx.m21 - pMtx.m01 * pMtx.m20);
		adjoint.m20 = (pMtx.m01 * pMtx.m12 - pMtx.m02 * pMtx.m11);
		adjoint.m21 = -(pMtx.m00 * pMtx.m12 - pMtx.m02 * pMtx.m10);
		adjoint.m22 = (pMtx.m00 * pMtx.m11 - pMtx.m01 * pMtx.m10);

		// Transpose adjoint matrix and save it in pResult
		Mtx33Transpose(*pResult, adjoint);

		// Divide each value in pResult by the determinant
		for (int i = 0; i < 9; ++i)
			pResult->m[i] /= *determinant;
	}
}
