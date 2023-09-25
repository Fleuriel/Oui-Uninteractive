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
bool CollisionStaticDynamicRectRect(AABB Rect1, AABB Rect2)
{
	
		////Smallest X-coordinate of both rectangle
		//float leftA, leftB{ 0 }; 
		//leftA = r1x - (s1 / 2);
		//leftB = r2x - (s2 / 2);

		////Biggest X-coordinate of both rectangle
		//float rightA, rightB{ 0 }; 
		//rightA = r1x + (s1 / 2);
		//rightB = r2x + (s2 / 2);

		////Biggest Y-coordinate of both rectangle
		//float topA, topB{ 0 }; 
		//topA = r1y + (s1 / 2);
		//topB = r2y + (s2 / 2);

		////Smallest Y-coordinate of both rectangle
		//float bottomA, bottomB{ 0 }; 
		//bottomA = r1y - (s1 / 2);
		//bottomB = r2y - (s2 / 2);
		
		//rightA = maxXFirstRect
		//leftB = 
		if ((Rect1.max.x > Rect2.min.x  && 
			 Rect1.max.y > Rect2.min.y) &&
			(Rect2.max.x > Rect1.min.x  &&
			 Rect2.max.y > Rect1.min.y))
		{
			std::cout << "ITS COLLIDING BOIS\n";
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

	//Velocity variables
	float RelativeVel_X = r2velocityX - r1velocityX;
	float RelativeVel_Y = r2velocityY - r1velocityY;

	//Timer variables
	float TimeFirst{ 0 };
	float TimeLast = static_cast<float>(GetDT());


	////////////////////
	///////X-Axis///////
	////////////////////
	
	//Time lesser than 0
	if (RelativeVel_X < 0) 
	{
		//Case 1
		if (leftA > rightB) 
		{
			return false;
		}

		//Case 4
		if (rightA < leftB)
		{
			TimeFirst = std::max(((rightA - leftB) / RelativeVel_X), TimeFirst);
		}
		if (leftA < rightB)
		{
			TimeLast = std::min(((leftA - rightB) / RelativeVel_X), TimeLast);
		}
	}

	//Time more than 0
	if (RelativeVel_X > 0)
	{
		//Case 2
		if (leftA > rightB)
		{
			TimeFirst = std::max(((leftA - rightB) / RelativeVel_X), TimeFirst);
		}
		if (rightA > leftB)
		{
			TimeLast = std::min(((rightA - leftB) / RelativeVel_X), TimeLast);
		}

		//Case 3
		if (rightA < leftB)
		{
			return false;
		}
	}

	//Final check
	if (TimeFirst > TimeLast)
	{
		return false; //No collision
	}

	////////////////////
	///////Y-Axis///////
	////////////////////
	
	//Time lesser than 0
	if (RelativeVel_Y < 0)
	{
		//Case 1
		if (bottomA > topB)
		{
			return false;
		}
		//Case 4
		if (topA < bottomB)
		{
			TimeFirst = std::max(((topA - bottomB) / RelativeVel_Y), TimeFirst);
		}
		if (bottomA < topB)
		{
			TimeLast = std::min(((bottomA - topB) / RelativeVel_Y), TimeLast);
		}
	}
	if (RelativeVel_Y > 0)
	{
		//Case 2
		if (bottomA > topB)
		{
			TimeFirst = std::max(((bottomA - topB) / RelativeVel_Y), TimeFirst);
		}
		if (topA > bottomB)
		{
			TimeLast = std::min(((topA - bottomB) / RelativeVel_Y), TimeLast);
		}

		//Case 3
		if (topA < bottomB)
		{
			return false;
		}
	}

	//Final check
	if (TimeFirst > TimeLast)
	{
		return false; //No collision
	}

	return false;
}

