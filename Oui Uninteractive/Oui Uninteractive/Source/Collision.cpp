#include "Collision.h"
#include <math.h>
#include "Vector2D.h"



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
		float leftA, leftB {0};
		leftA = r1x - (s1 / 2) ;
		leftB = r2x - (s2 / 2) ;

		float rightA, rightB {0};
		rightA = r1x + (s1 / 2) ;
		rightB = r2x + (s2 / 2) ;

		float topA, topB {0};
		topA = r1y - (s1 / 2) ;
		topB = r2y - (s2 / 2) ;

		float bottomA, bottomB {0};
		bottomA = r1y + (s1 / 2) ;
		bottomB = r2y + (s2 / 2) ;

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