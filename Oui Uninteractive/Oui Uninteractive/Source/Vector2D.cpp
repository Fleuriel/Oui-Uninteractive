/**************************************************************************
* @file Vector2D.cpp
* @author CHEAH Tristan Tze Hong
* @co-author CHAN Aaron Jun Xiang
* @par DP email: t.cheah@digipen.edu
* @par Course: CSD 2401
* @par Software Engineering Project 3
* @date 05-09-2023
* @brief This file contains the definition of functions for Vector2D
*************************************************************************/
#include "Vector2D.h"
#include <cmath>
#include <Global.h>
/**************************************************************************
* @brief Operator overload for +=
* @param rhs - the vector to add
* @return Vector2D&
*************************************************************************/
Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
	*this = *this + rhs;
	return *this;
}

/**************************************************************************
* @brief Operator overload for -=
* @param rhs - the vector to subtract
* @return Vector2D&
**************************************************************************/
Vector2D& Vector2D::operator-=(const Vector2D& rhs) {
	*this = *this - rhs;
	return *this;
}

/**************************************************************************
* @brief Operator overload for *=
* @param rhs - the scalar multiple
* @return Vector2D &
**************************************************************************/
Vector2D& Vector2D::operator*=(float rhs) {
	*this = *this * rhs;
	return *this;
}

/**************************************************************************
* @brief Operator overload for /=
* @param rhs - the divisor
* @return Vector2D &
**************************************************************************/
Vector2D& Vector2D::operator/=(float rhs) {
	*this = *this / rhs;
	return *this;
}

/**************************************************************************
* @brief Operator overload unary minus, this function negates the vector
* @return Vector2D 
**************************************************************************/
Vector2D Vector2D::operator-() const {
	return Vector2D(-x,-y);
}



/**************************************************************************
* @brief Operator overload for +, adds two vector together
* @param lhs - operand one 
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs) {
	return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}
	
/**************************************************************************
* @brief Operator overload for -, subtracts two vector
* @param lhs - operand one 
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) {
	return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
}

/**************************************************************************
* @brief Operator overload for *, multiplies a vector and a float
* @param lhs - operand one
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator*(const Vector2D& lhs, float rhs) {
	return Vector2D(lhs.x * rhs , lhs.y * rhs);
}

/**************************************************************************
* @brief Operator overload for *, multiplies a vector and a float
* @param lhs - operand one
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator*(float lhs, const Vector2D& rhs) {
	return rhs*lhs;
}

/**************************************************************************
* @brief Operator overload for /, divides a vector and a float
* @param lhs - operand one
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator/(const Vector2D& lhs, float rhs) {
		return Vector2D(lhs.x / rhs, lhs.y / rhs);
}

Vector2D operator/(const Vector2D& lhs, const Vector2D& rhs) {
	return Vector2D(lhs.x / rhs.x, lhs.y / rhs.y);
}

Vector2D operator*(const Vector2D& lhs, const Vector2D& rhs) {
	return Vector2D(lhs.x * rhs.x, lhs.y * rhs.y);
}
/**************************************************************************
* @brief Normalizes a vector, returns result to pResult
* @param pResult - the vector to write to
* @param pVec0 - the vector to normalize
* @return void
**************************************************************************/
void Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0) {
	if (pVec0.x == 0 && pVec0.y == 0) {
		pResult = Vec2(0, 0);
	}
	else {
		pResult = pVec0 / Vector2DLength(pVec0);
	}
	
}

/**************************************************************************
* @brief Returns length of a vector
* @param pVec0 - the vector to calculate from
* @return float
**************************************************************************/
float Vector2DLength(const Vector2D& pVec0) {
	return static_cast<float>(sqrt(pow(pVec0.x, 2.0) + pow(pVec0.y, 2.0)));
}

/**************************************************************************
* @brief Returns the square of the length of a vector
* @param pVec0 - the vector to calculate from
* @return float
**************************************************************************/
float Vector2DSquareLength(const Vector2D& pVec0) {
	return static_cast<float>(pow(pVec0.x, 2.0) + pow(pVec0.y, 2.0));
}

/**************************************************************************
* @brief Returns the distance between two points
* @param pVec0 - the point to calculate from
* @param pVec1 - the 2nd point to calculate from
* @return float
**************************************************************************/
float Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1) {
	return Vector2DLength(Vector2D(pVec1.x - pVec0.x, pVec1.y - pVec0.y));
}

/**************************************************************************
* @brief Returns the squared distance between two points
* @param pVec0 - the point to calculate from
* @param pVec1 - the 2nd point to calculate from
* @return float
**************************************************************************/
float Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1) {
	return Vector2DSquareLength(Vector2D(pVec1.x - pVec0.x, pVec1.y - pVec0.y));
}

/**************************************************************************
* @brief Returns the dot product of two vectors
* @param pVec0 - the vector to calculate from
* @param pVec1 - the 2nd vector to calculate from
* @return float
**************************************************************************/
float Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1) {
	return pVec0.x * pVec1.x + pVec0.y * pVec1.y;
}

/**************************************************************************
* @brief Returns the cross product of two vectors
* @param pVec0 - the vector to calculate from
* @param pVec1 - the 2nd vector to calculate from
* @return float
**************************************************************************/
float Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1) {
	return pVec0.x * pVec1.y - pVec0.y * pVec1.x;
}
