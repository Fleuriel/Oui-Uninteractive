/**************************************************************************
 * @file RandomUtilities.cpp
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <RandomUtilities.h>
#include <random>



std::random_device rd;
std::default_random_engine random(rd());



/*  _________________________________________________________________________*/

/*! float rand_uniform_float(float min, float max)

@brief
	This fucntion is used to get the random uniform float number.

@param min
		minimum value

@param max
		maximum value

@return uniform_real_distribution<float>
		a random float value that is between the min and max value.
*/
float rand_uniform_float(float min, float max)
{
	std::uniform_real_distribution<float> rand_float_value(min, std::nextafter(max, std::numeric_limits<float>::max()));
	return rand_float_value(random);
}


/*  _________________________________________________________________________*/

/*! float rand_float(float min, float max)

@brief
	This fucntion is used to get the random float number.

@param min
		minimum value < Default Value 0.0f >

@param max
		maximum value < Default Value 1.0f >

@return float
		a random float value that is between the min and max value.
*/
float rand_float(float min, float max)
{
	return min + ((max - min) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
}

/*  _________________________________________________________________________*/

/*! float rand_int(int min, int max)

@brief
	This fucntion is used to get the random float number.

@param min
		minimum value 

@param max
		maximum value 

@return int
		a random int value that is between the min and max value.
*/
int rand_int(int min, int max)
{
	std::uniform_int_distribution<int> rand_int_value(min, static_cast<int>(std::nextafter(max, std::numeric_limits<float>::max())));
	return rand_int_value(random);
}
