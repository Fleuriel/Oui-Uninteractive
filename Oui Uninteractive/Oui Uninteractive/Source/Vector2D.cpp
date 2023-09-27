/**************************************************************************
* @file Vector2D.cpp
* @author CHEAH Tristan Tze Hong
* @par DP email: t.cheah@digipen.edu
* @par Course: CSD 2401
* @par Software Engineering Project 3
* @date 05-09-2023
* @brief This file contains the definition of functions for Vector2D
*************************************************************************/
#include "Vector2D.h"
#include <cmath>
#include <Global.h>

/**************************************************************************/
/*!
	This function adds vector rhs to the current vector
*/
/**************************************************************************/
Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
	*this = *this + rhs;
	return *this;
}

/**************************************************************************/
/*!
	This function subtracts vector rhs from the current vector
*/
/**************************************************************************/
Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
	*this = *this - rhs;
	return *this;
}

/**************************************************************************/
/*!
	This function multiplies the values of a vector by scalar rhs
*/
/**************************************************************************/
Vector2D& Vector2D::operator*=(float rhs)
{
	*this = *this * rhs;
	return *this;
}

/**************************************************************************/
/*!
	This function divides the values of a vector by scalar rhs
*/
/**************************************************************************/
Vector2D& Vector2D::operator/=(float rhs)
{
	*this = *this / rhs;
	return *this;
}

/**************************************************************************/
/*!
	This function flips the sign of a vector
*/
/**************************************************************************/
Vector2D Vector2D::operator-() const
{
	return Vector2D(-x,-y);
}

/**************************************************************************/
/*!
	This function adds 2 vectors (lhs + rhs)
*/
/**************************************************************************/
Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}
	
/**************************************************************************/
/*!
	This function subtracts 2 vectors (lhs - rhs)
*/
/**************************************************************************/
Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
}

/**************************************************************************/
/*!
	This function multiplies the values of a vector by scalar rhs
*/
/**************************************************************************/
Vector2D operator*(const Vector2D& lhs, float rhs)
{
	return Vector2D(lhs.x * rhs , lhs.y * rhs);
}

/**************************************************************************/
/*!
	This function multiplies the values of a vector by scalar lhs
*/
/**************************************************************************/
Vector2D operator*(float lhs, const Vector2D& rhs)
{
	return rhs*lhs;
}

/**************************************************************************/
/*!
	This function divides the values of a vector by scalar rhs
*/
/**************************************************************************/
Vector2D operator/(const Vector2D& lhs, float rhs)
{
	return Vector2D(lhs.x / rhs, lhs.y / rhs);
}


/**************************************************************************/
/*!
	In this function, pResult will be the unit vector of pVec0
*/
/**************************************************************************/
void Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0)
{
	pResult = pVec0 / Vector2DLength(pVec0);
}

/**************************************************************************/
/*!
	This function returns the length of the vector pVec0
*/
/**************************************************************************/
float Vector2DLength(const Vector2D& pVec0)
{
	return static_cast<float>(sqrt(pow(pVec0.x, 2.0) + pow(pVec0.y, 2.0)));
}

/**************************************************************************/
/*!
	This function returns the square of pVec0's length. Avoid the square root
*/
/**************************************************************************/
float Vector2DSquareLength(const Vector2D& pVec0)
{
	return static_cast<float>(pow(pVec0.x, 2.0) + pow(pVec0.y, 2.0));
}

/**************************************************************************/
/*!
	In this function, pVec0 and pVec1 are considered as 2D points.
	The distance between these 2 2D points is returned
*/
/**************************************************************************/
float Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1)
{
	return Vector2DLength(Vector2D(pVec1.x - pVec0.x, pVec1.y - pVec0.y));
}

/**************************************************************************/
/*!
	In this function, pVec0 and pVec1 are considered as 2D points.
	The squared distance between these 2 2D points is returned.
	Avoid the square root
*/
/**************************************************************************/
float Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1)
{
	return Vector2DSquareLength(Vector2D(pVec1.x - pVec0.x, pVec1.y - pVec0.y));
}

/**************************************************************************/
/*!
	This function returns the dot product between pVec0 and pVec1
*/
/**************************************************************************/
float Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1)
{
	return pVec0.x * pVec1.x + pVec0.y * pVec1.y;
}

/**************************************************************************/
/*!
	This function returns the cross product magnitude
	between pVec0 and pVec1
*/
/**************************************************************************/
float Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1)
{
	return pVec0.x * pVec1.y - pVec0.y * pVec1.x;
}
