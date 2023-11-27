/**************************************************************************
* @file Matrix3x3.h
* @author HWANG Jing Rui, Austin - 100%
* @par DP email: jingruiaustin.hwang@digipen.edu
* @par Course: CSD 2401
* @par Software Engineering Project 3
* @date 05-09-2023
* @brief This file contains the declaration of functions for Matrix3x3
*************************************************************************/
#pragma once

#include "Vector2D.h"

#ifdef _MSC_VER
// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( disable : 4201 )
#endif

typedef union Matrix3x3
{
	struct 
	{
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;
	};

	float m[9];
	float m2[3][3];

	/**************************************************************************
	* @brief Default Constructor
	*************************************************************************/
	Matrix3x3() : m00(0.0f), m01(0.0f), m02(0.0f), m10(0.0f), m11(0.0f), m12(0.0f), m20(0.0f), m21(0.0f), m22(0.0f) {}

	/**************************************************************************
	* @brief Constructor (array)
	*************************************************************************/
	Matrix3x3(const float *pArr);

	/**************************************************************************
	* @brief Constructor (individual values)
	*************************************************************************/
	Matrix3x3(float _00, float _01, float _02,
				float _10, float _11, float _12,
				float _20, float _21, float _22);

	/**************************************************************************
	* @brief Copy Assignment
	*************************************************************************/
	Matrix3x3& operator=(const Matrix3x3 &rhs);

	/**************************************************************************
	* @brief Copy Constructor
	* @param rhs - the second matrix
	*************************************************************************/
	Matrix3x3(const Matrix3x3& rhs) = default;

	/**************************************************************************
	* @brief Cross product 2 matrices and save the resultant matrix in the 
			current matrix
	* @param rhs - the second matrix
	* @return Matrix3x3&
	*************************************************************************/
	Matrix3x3& operator*=(const Matrix3x3& rhs);

} Matrix3x3, Mtx33;

#ifdef _MSC_VER
// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( default : 4201 )
#endif

/**************************************************************************
* @brief Cross product of 2 matrices
* @param lhs - first matrix
* @param rhs - second matrix
* @return Matrix3x3 - resultant matrix
*************************************************************************/
Mtx33 operator* (const Mtx33& lhs, const Mtx33& rhs);

/**************************************************************************
* @brief Multiply the matrix pMtx with the vector rhs
* @param pMtx - matrix
* @param rhs - vector
* @return Vector2D - resultant vector
*************************************************************************/
Vec2 operator* (const Mtx33& pMtx, const Vec2& rhs);

/**************************************************************************
* @brief Set the matrix pResult to the identity matrix
* @param pResult - matrix
* @return void
*************************************************************************/
void Mtx33Identity(Mtx33& pResult);

/**************************************************************************
* @brief Create a translation matrix from x & y	and save it in pResult
* @param pResult - matrix
* @param x - x value
* @param y - y value
* @return void
*************************************************************************/
void Mtx33Translate(Mtx33& pResult, float x, float y);
	
/**************************************************************************/
/*!
	This function creates a scaling matrix from x & y 
	and saves it in pResult
	*/
/**************************************************************************/
void Mtx33Scale(Mtx33& pResult, float x, float y);
	
/**************************************************************************
* @brief Create a rotation matrix from "angle" whose value is in radian. 
*		 Save the resultant matrix in pResult.
* @param pResult - matrix
* @param angle - angle of rotation (radian)
* @return void
*************************************************************************/
void Mtx33RotRad(Mtx33& pResult, float angle);
	
/**************************************************************************
* @brief Create a rotation matrix from "angle" whose value is in degree.
*		 Save the resultant matrix in pResult.
* @param pResult - matrix
* @param angle - angle of rotation (degree)
* @return void
*************************************************************************/
void Mtx33RotDeg(Mtx33& pResult, float angle);
	
/**************************************************************************
* @brief Calculate the transpose matrix of pMtx and save it in pResult.
* @param pResult - resultant matrix
* @param pMtx - matrix to transpose
* @return void
*************************************************************************/
void Mtx33Transpose(Mtx33& pResult, const Mtx33& pMtx);

/**************************************************************************
* @brief Calculate the inverse matrix of pMtx and save the result in pResult. 
*		 If the matrix inversion fails, pResult would be set to NULL.
* @param pResult - resultant matrix
* @param determinant
* @param pMtx - matrix to inverse
* @return void
*************************************************************************/
void Mtx33Inverse(Mtx33* pResult, float* determinant, const Mtx33& pMtx);
