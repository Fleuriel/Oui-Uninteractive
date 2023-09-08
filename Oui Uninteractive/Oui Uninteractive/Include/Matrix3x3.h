/**************************************************************************
* @file InputKeys.cpp
* @author
* @par DP email:
* @par Course: CSD 2401
* @par Software Engineering Project 3
* @date 09-05-2023
* @brief
*************************************************************************/
#pragma once

#include "Vector2D.h"

#ifdef _MSC_VER
// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( disable : 4201 )
#endif

/**************************************************************************/
/*!

	*/
/**************************************************************************/
typedef union Matrix3x3
{
	struct 
	{
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;
	};

	float m[9];
	float m2[3][3];//You need this for the second part of the assignment

	Matrix3x3() : m00(0.0f), m01(0.0f), m02(0.0f), m10(0.0f), m11(0.0f), m12(0.0f), m20(0.0f), m21(0.0f), m22(0.0f) {}
	Matrix3x3(const float *pArr);
	Matrix3x3(float _00, float _01, float _02,
				float _10, float _11, float _12,
				float _20, float _21, float _22);
	Matrix3x3& operator=(const Matrix3x3 &rhs);

	//Do not change the following
	Matrix3x3(const Matrix3x3& rhs) = default;

	// Assignment operators
	Matrix3x3& operator *= (const Matrix3x3 &rhs);

} Matrix3x3, Mtx33;

#ifdef _MSC_VER
// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( default : 4201 )
#endif

Matrix3x3 operator * (const Matrix3x3 &lhs, const Matrix3x3 &rhs);
	
/**************************************************************************/
/*!
	This operator multiplies the matrix pMtx with the vector rhs 
	and returns the result as a vector
	*/
/**************************************************************************/
Vector2D  operator * (const Matrix3x3 &pMtx, const Vector2D &rhs);
	
/**************************************************************************/
/*!
	This function sets the matrix pResult to the identity matrix
	*/
/**************************************************************************/
void Mtx33Identity(Matrix3x3 &pResult);
	
/**************************************************************************/
/*!
	This function creates a translation matrix from x & y 
	and saves it in pResult
	*/
/**************************************************************************/
void Mtx33Translate(Matrix3x3 &pResult, float x, float y);
	
/**************************************************************************/
/*!
	This function creates a scaling matrix from x & y 
	and saves it in pResult
	*/
/**************************************************************************/
void Mtx33Scale(Matrix3x3 &pResult, float x, float y);
	
/**************************************************************************/
/*!
	This matrix creates a rotation matrix from "angle" whose value 
	is in radian. Save the resultant matrix in pResult.
	*/
/**************************************************************************/
void Mtx33RotRad(Matrix3x3 &pResult, float angle);
	
/**************************************************************************/
/*!
	This matrix creates a rotation matrix from "angle" whose value 
	is in degree. Save the resultant matrix in pResult.
	*/
/**************************************************************************/
void Mtx33RotDeg(Matrix3x3 &pResult, float angle);
	
/**************************************************************************/
/*!
	This functions calculated the transpose matrix of pMtx 
	and saves it in pResult
	*/
/**************************************************************************/
void Mtx33Transpose(Matrix3x3 &pResult, const Matrix3x3 &pMtx);
	
/**************************************************************************/
/*!
	This function calculates the inverse matrix of pMtx and saves the 
	result in pResult. If the matrix inversion fails, pResult 
	would be set to NULL.
*/
/**************************************************************************/
void Mtx33Inverse(Matrix3x3 *pResult, float *determinant, const Matrix3x3 &pMtx);