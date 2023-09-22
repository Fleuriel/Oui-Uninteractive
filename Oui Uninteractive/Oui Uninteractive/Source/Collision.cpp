#include "Collision.h"
#include <math.h>
#include "Vector2D.h"
#include "GameStateManager.h"



/**************************************************************************
 * @brief Check for collision between static circles
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param Vector2DDistance The distance between two the two coordinates
 * @param r1 Radius of the first circle
 * @param r2 Radius of the second circle
 *************************************************************************/
bool CollisionStaticCircleCircle(Coordinates Coords1, Coordinates Coords2, float r1=2, float r2=2)
{
	float RadiusTotal = r1 + r2;
	return (Coords1.DistanceIsWithinThreshold(Coords2, (RadiusTotal)));
}

/**************************************************************************
 * @brief Check for collision between static rectangles
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param Vector2DDistance The distance between two the two coordinates
 * @param 
 * @param 
 *************************************************************************/
bool CollisionStaticRectRect(float r1x=2,float r1y=2,float r2x=2,float r2y=2, float s1=3, float s2=3)
{
		//Smallest X-coordinate of both rectangle
		float leftA, leftB{ 0 }; 
		leftA = r1x - (s1 / 2);
		leftB = r2x - (s2 / 2);

		//Biggest X-coordinate of both rectangle
		float rightA, rightB{ 0 }; 
		rightA = r1x + (s1 / 2);
		rightB = r2x + (s2 / 2);

		//Biggest Y-coordinate of both rectangle
		float topA, topB{ 0 }; 
		topA = r1y + (s1 / 2);
		topB = r2y + (s2 / 2);

		//Smallest Y-coordinate of both rectangle
		float bottomA, bottomB{ 0 }; 
		bottomA = r1y - (s1 / 2);
		bottomB = r2y - (s2 / 2);

		if ((rightA > leftB  && 
			 topA > bottomB) &&
			(rightB > leftA  &&
			 topB > bottomA))
		{
		return true;
		}
		else 
		{
		return false;
		}

		//if(leftA > rightB) then no collision
		//if(leftB > rightA) then no collision
		//if(topA < bottomB) then no collision
		//if(topB < bottomA) then no collision

}

bool CollisionMovingRectRect(float r1x = 1, float r1y = 2, float r2x = 3, float r2y = 4, 
							 float r1velocityX = 5, float r1velocityY = 6, float r2velocityX = 7, float r2velocityY = 8,
							 float s1 = 9, float s2 = 10)
{
	//Smallest X-coordinate of both rectangle
	float leftA, leftB{ 0 };
	leftA = r1x - (s1 / 2);
	leftB = r2x - (s2 / 2);

	//Biggest X-coordinate of both rectangle
	float rightA, rightB{ 0 };
	rightA = r1x + (s1 / 2);
	rightB = r2x + (s2 / 2);

	//Biggest Y-coordinate of both rectangle
	float topA, topB{ 0 };
	topA = r1y + (s1 / 2);
	topB = r2y + (s2 / 2);

	//Smallest Y-coordinate of both rectangle
	float bottomA, bottomB{ 0 };
	bottomA = r1y - (s1 / 2);
	bottomB = r2y - (s2 / 2);

	float RelativeVel_X = r2velocityX - r1velocityX;
	float RelativeVel_Y = r2velocityY - r1velocityY;
	float TimeFirstX{ 0 };
	float TimeFirstY{ 0 };
	float TimeLastX{ 0 };
	float TimeLastY{ 0 };

	//TEMPORARY TIMER
	float FrameTime = GetDT();
	


	//Check for whether Relative velocity of X is lesser than 0
	if (RelativeVel_X < 0)
	{
		if (leftA > rightB)
			return false;

		else 
		{
			TimeFirstX = (rightA - leftB) / RelativeVel_X;
			TimeLastX = (leftA - rightB) / RelativeVel_X;
		}
	}

	else
	{
		if (leftA > rightB)
		{
			TimeFirstX = (leftA - rightB) / RelativeVel_X;
			TimeLastX = (rightA - leftB) / RelativeVel_X;
		}
		else
		{
			return false;
		}
	}
	//Check for relative velocity of y coordinate is lesser than 0
	if (RelativeVel_Y < 0)
	{
		if (bottomA > topA)
		{
			return false;
		}
		else
		{
			TimeFirstY = (topA - bottomB) / RelativeVel_Y;
			TimeLastX = (bottomA - topB) / RelativeVel_Y;
		}
	}
	//Checks if not lesser than 0
	else
	{
		if (bottomA > topB)
		{
			TimeFirstY = (bottomA - topB) / RelativeVel_Y;
			TimeLastY = (topA - bottomB) / RelativeVel_Y;
		}
		else
		{
			return false;
		}
	}

	//Compare time, if 
	if (TimeFirstY > TimeLastX || TimeFirstX > TimeLastY)
	{
		return false;
	}

	if (TimeFirstX > TimeFirstY)
	{
		if (TimeFirstX < 0 || TimeFirstX > FrameTime)
		{
			return false;
		}
	}
	else
	{
		if (TimeFirstY < 0 || TimeFirstY > FrameTime) {
			return false;
		}
	}

	//There is collision
	return true;

}