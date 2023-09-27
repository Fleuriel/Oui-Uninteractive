/**************************************************************************
* @file Vector2D.h
* @author CHEAH Tristan Tze Hong
* @par DP email: t.cheah@digipen.edu
* @par Course: CSD 2401
* @par Software Engineering Project 3
* @date 05-09-2023
* @brief This file contains the declaration of functions for Vector2D
*************************************************************************/
#pragma once

#ifdef _MSC_VER
// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( disable : 4201 )
#endif
# define M_PI           3.14159265358979323846
/**************************************************************************/
/*!

	*/
/**************************************************************************/
typedef union Vector2D
{
	struct
	{
		float x, y;
	};

	float m[2];

	// Constructors
	Vector2D() : x(0.0f), y(0.0f) {};
	Vector2D(float _x, float _y) : x(_x), y(_y) {};

	//Do not change the following
	// Copy Assignment Operator 
	Vector2D& operator=(const Vector2D& rhs) = default;
	//Copy Constructor
	Vector2D(const Vector2D & rhs) = default;

	// Assignment operators
	/**************************************************************************
	* @brief Operator overload for +=
	* @param rhs - the vector to add
	* @return Vector2D&
	*************************************************************************/
	Vector2D& operator += (const Vector2D &rhs);
	/**************************************************************************
	* @brief Operator overload for -=
	* @param rhs - the vector to subtract
	* @return Vector2D&
	**************************************************************************/
	Vector2D& operator -= (const Vector2D &rhs);
	/**************************************************************************
	* @brief Operator overload for *=
	* @param rhs - the scalar multiple
	* @return Vector2D &
	**************************************************************************/
	Vector2D& operator *= (float rhs);
	/**************************************************************************
	* @brief Operator overload for /=
	* @param rhs - the divisor
	* @return Vector2D &
	**************************************************************************/
	Vector2D& operator /= (float rhs);

	// Unary operators
	/**************************************************************************
	* @brief Operator overload unary minus, this function negates the vector
	* @return Vector2D
	**************************************************************************/
	Vector2D operator -() const;

} Vector2D, Vec2, Point2D, Pt2;


#ifdef _MSC_VER
// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( default : 4201 )
#endif

// Binary operators
/**************************************************************************
* @brief Operator overload for +, adds two vector together
* @param lhs - operand one
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator + (const Vector2D &lhs, const Vector2D &rhs);
/**************************************************************************
* @brief Operator overload for -, subtracts two vector
* @param lhs - operand one
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator - (const Vector2D &lhs, const Vector2D &rhs);
/**************************************************************************
* @brief Operator overload for *, multiplies a vector and a float
* @param lhs - operand one
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator * (const Vector2D &lhs, float rhs);

/**************************************************************************
* @brief Operator overload for *, multiplies a vector and a float
* @param lhs - operand one
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator * (float lhs, const Vector2D &rhs);
/**************************************************************************
* @brief Operator overload for /, divides a vector and a float
* @param lhs - operand one
* @param rhs - operand two
* @return Vector2D
**************************************************************************/
Vector2D operator / (const Vector2D &lhs, float rhs);

/**************************************************************************
* @brief Normalizes a vector, returns result to pResult
* @param pResult - the vector to write to
* @param pVec0 - the vector to normalize
* @return void
**************************************************************************/
void	Vector2DNormalize(Vector2D &pResult, const Vector2D &pVec0);
	
/**************************************************************************
* @brief Returns length of a vector
* @param pVec0 - the vector to calculate from
* @return float
**************************************************************************/
float	Vector2DLength(const Vector2D &pVec0);
	
/**************************************************************************
* @brief Returns the square of the length of a vector
* @param pVec0 - the vector to calculate from
* @return float
**************************************************************************/
float	Vector2DSquareLength(const Vector2D &pVec0);
	
/**************************************************************************
* @brief Returns the distance between two points
* @param pVec0 - the point to calculate from
* @param pVec1 - the 2nd point to calculate from
* @return float
**************************************************************************/
float	Vector2DDistance(const Vector2D &pVec0, const Vector2D &pVec1);
	
/**************************************************************************
* @brief Returns the squared distance between two points
* @param pVec0 - the point to calculate from
* @param pVec1 - the 2nd point to calculate from
* @return float
**************************************************************************/
float	Vector2DSquareDistance(const Vector2D &pVec0, const Vector2D &pVec1);
	
/**************************************************************************
* @brief Returns the dot product of two vectors
* @param pVec0 - the vector to calculate from
* @param pVec1 - the 2nd vector to calculate from
* @return float
**************************************************************************/
float	Vector2DDotProduct(const Vector2D &pVec0, const Vector2D &pVec1);
	
/**************************************************************************
* @brief Returns the cross product of two vectors
* @param pVec0 - the vector to calculate from
* @param pVec1 - the 2nd vector to calculate from
* @return float
**************************************************************************/
float	Vector2DCrossProductMag(const Vector2D &pVec0, const Vector2D &pVec1);
