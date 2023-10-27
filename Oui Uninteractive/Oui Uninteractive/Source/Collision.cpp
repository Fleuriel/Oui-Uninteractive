/**************************************************************************
 * @file		  Collision.cpp
 * @author		  QUEK Cheng Kwang Emery
 * @par DP email: c.quek@digipen.edu
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-25-2023
 * @brief		  This is a source file containing the functions of 
 *				  various collisions such as static circles,
 *				  dynamic static rectangles, and dynamic rectangles
 *************************************************************************/

#include "Collision.h"




/**************************************************************************
 * @brief Check for collision for mouse and rectangle
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param AABB Rect1 The Coordinates (x,y) of the rectangle
 *************************************************************************/
bool CollisionMouseRect(Collider::AABB Rect1) {

	double xpos, ypos{};
	glfwGetCursorPos(windowNew, &xpos, &ypos);

	if ((Rect1.max.x > xpos &&
		Rect1.max.y > ypos) &&
		(xpos > Rect1.min.x &&
		 ypos > Rect1.min.y)){
		std::cout << "Collision detected\n";
		return true;
	}
	else{
		return false;
	}
}


/**************************************************************************
 * @brief Check for collision for mouse and circle
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param Vector2DDistance The distance between two the two coordinates
 * @param Coords1 The coordinates of the shape
 * @param r1 The size of the shape
 *************************************************************************/
bool CollisionMouseCircle(Coordinates Coords1, float r1 = 2) {

	double xpos, ypos{};
	glfwGetCursorPos(windowNew, &xpos, &ypos);
	
	return (Coords1.DistanceIsWithinThreshold(Coordinates(static_cast<float>(xpos), static_cast<float>(ypos)), (r1)));
}


/**************************************************************************
 * @brief Check for collision between static circles
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param Coords1 Coordinates(x,y) of first circle
 * @param Coords2 Coordinates(x,y) of second circle
 * @param r1 Radius of the first circle
 * @param r2 Radius of the second circle
 *************************************************************************/
bool CollisionStaticCircleCircle(Coordinates Coords1, Coordinates Coords2, float r1=2, float r2=2) {
	float RadiusTotal = r1 + r2;
	return (Coords1.DistanceIsWithinThreshold(Coords2, (RadiusTotal)));
}

/**************************************************************************
 * @brief Check for collision between static-dynamic rectangles
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param Rect1 Coordinates of the first rectangle
 * @param Rect2 Coordinates of the second rectangle
 *************************************************************************/
bool CollisionStaticDynamicRectRect(Collider::AABB Rect1, Collider::AABB Rect2) {
		if ((Rect1.max.x > Rect2.min.x  && 
			 Rect1.max.y > Rect2.min.y) &&
			(Rect2.max.x > Rect1.min.x  &&
			 Rect2.max.y > Rect1.min.y)) {
		//std::cout << "Collision detected\n";
		//std::cout << "X " << physicsSys->bodyList[0]->txPtr->position.x << "Y " << physicsSys->bodyList[0]->txPtr->position.y << " \n";
		//std::cout << Rect1.max.x << " " << Rect1.center.x;
		//Vector2D direction;
		//direction = Rect2.center - Rect1.center;
		////std::cout << "Direction X: " << direction.x << "Direction Y: " << direction.y << "\n";
		////std::cout << "Direction: " << direction.center.x << " " << direction.center.y;
		//
		//Vector2D Rect1norm;

		//Vector2DNormalize(Rect1norm, direction);

		//if (Vector2DDotProduct(direction, Rect1norm) < 0.f) {
		//	Rect1norm = -Rect1norm;
		//	physicsSys->bodyList[0]->velocity = Rect1norm;
		//}
		//
		
		//physicsSys->bodyList[0]->velocity.x = -20;
		//physicsSys->bodyList[0]->velocity.y = -20;
		
		
		return true;
		}
		else {
		return false;
		}
}


/**************************************************************************
 * @brief Check for collision between moving rectangles
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param r1x, r2x X-coordinates of first and second rectangle respectively
 * @param r1y, r2y Y-coordinates of first and second rectangle respectively
 * @param r1velocityX, r1velocityY, r2velocityX, r2velocityY 
		  velocities of each coordinate points
 * @param s1, s2  Width of first and second rectangle respectively
 *************************************************************************/

float CalculateEntryTimeAndNormal(Collider::AABB* Rect1, Collider::AABB* Rect2, Vec2 Rect1Vel, float& normalX, float& normalY) {
	float distanceXEntry;
	float distanceYEntry;

	if (Rect1Vel.x < 0) {
		distanceXEntry = Rect2->max.x - Rect1->min.x;
	}
	else {
		distanceXEntry = Rect2->min.x - Rect1->max.x;
	}
	
	if (Rect1Vel.y < 0) {
		distanceYEntry = Rect2->max.y - Rect1->min.y;
	}
	else {
		distanceYEntry = Rect2->min.y - Rect1->max.y;
	}

	if (abs(distanceXEntry) < abs(distanceYEntry)) {
		//if distance is negative, i am coming from the left
		// else coming from the right
		if (distanceXEntry < 0) {
			normalX = 1;
			return distanceXEntry;
		}
		else {
			normalX = -1;
			return -distanceXEntry;
		}
		std::cout << "X AXIS\n";
		
	}
	else {
		//negative from bottom
		//positive from top
		if (distanceYEntry < 0) {
			normalY = 1;
			return distanceYEntry;
		}
		else {
			normalY = -1;
			return -distanceYEntry;
		}

 		std::cout << " Y AXIS";
		
	}
	
	//min of static - max of dynamic
	//float distanceXEntry, distanceYEntry;
	//float distanceXExit, distanceYExit;
	//if (Rect1Vel.x > 0.0f) {
	//	distanceXEntry = Rect2->min.x - Rect1->max.x;
	//	distanceXExit = Rect2->max.x - Rect1->min.x;
	//}
	//else {
	//	distanceXEntry = Rect2->max.x - Rect1->min.x;
	//	distanceXExit = Rect2->min.x - Rect1->max.x;
	//}

	//if (Rect1Vel.y > 0.0f) {
	//	distanceYEntry = Rect2->max.y - Rect1->min.y;
	//	distanceYExit = Rect2->min.y - Rect1->max.y;
	//}
	//else {
	//	distanceYEntry = Rect2->min.y - Rect1->max.y;
	//	distanceYExit = Rect2->max.y - Rect1->min.y;
	//}

	//float xEntryTime, yEntryTime;
	//float xExitTime, yExitTime;

	//if (Rect1Vel.x == 0.0f)
	//{
	//	
	//}
	//else
	//{
	//	xEntryTime = distanceXEntry / Rect1Vel.x;
	//	xExitTime = distanceXExit / Rect1Vel.x;
	//}

	//if (Rect1Vel.y == 0.0f)
	//{
	//
	//}
	//else
	//{
	//	yEntryTime = distanceYEntry / Rect1Vel.y;
	//	yExitTime = distanceYExit / Rect1Vel.y;
	//}
	//float entryTime = std::min(xEntryTime, yEntryTime);
	//float exitTime = std::min(xExitTime, yExitTime);

	//if (entryTime > exitTime || (xEntryTime < 0.0f && yEntryTime < 0.0f) || xEntryTime > 1.0f || yEntryTime > 1.0f) {
	//	normalX = 0.0f;
	//	normalY = 0.0f;
	//	return 1.0f;
	//}
	//else // if there was a collision 
	//{
	//	// calculate normal of collided surface
	//	if (xEntryTime > yEntryTime)
	//	{
	//		if (distanceXEntry < 0.0f)
	//		{
	//			normalX = 1.0f;
	//			normalY = 0.0f;
	//		}
	//		else
	//		{
	//			normalX = -1.0f;
	//			normalY = 0.0f;
	//		}
	//	}
	//	else
	//	{
	//		if (distanceYEntry < 0.0f)
	//		{
	//			normalX = 0.0f;
	//			normalY = 1.0f;
	//		}
	//		else
	//		{
	//			normalX = 0.0f;
	//			normalY = -1.0f;
	//		}
	//	} // return the time of collisionreturn entryTime; 
	//	return entryTime;
	//}
}
float CollisionMovingRectRect(Collider::AABB Rect1, Collider::AABB Rect2, Vec2 Rect1Vel, Vec2 Rect2Vel) {
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

	//Velocity variables
	Vec2 RelativeVel = Rect2Vel - Rect1Vel;

	if (Vector2DLength(RelativeVel) == 0) {
		return false;
	}
	

	//Timer variables
	float TimeFirst{ 0 };
	float TimeLast = static_cast<float>(GetDT());

	float dFirstX = Rect1.min.x - Rect2.max.x;
	float dLastX = Rect1.max.x - Rect2.min.x;
	////////////////////
	///////X-Axis///////
	////////////////////
	
	//Time lesser than 0
	if (RelativeVel.x < 0) {
		//Case 1
		if (Rect1.min.x > Rect2.max.x) {
			return false;
		}

		//Case 4
		if (Rect1.max.x < Rect2.min.x) {
			
			if ((dFirstX / RelativeVel.x) > TimeFirst) { //Case 4
				TimeFirst = (dFirstX / RelativeVel.x);
			}
			if ((dLastX / RelativeVel.x) < TimeLast) {
				TimeLast = dLastX / RelativeVel.x;
			}
		}
	}
	//Time more than 0
	if (RelativeVel.x > 0) {
		if (Rect1.max.x > Rect2.min.x) {
			if ((dFirstX / RelativeVel.x) > TimeFirst) {
				TimeFirst = dFirstX / RelativeVel.x; // Case 2
			}
			if ((dLastX / RelativeVel.x) < TimeLast) {
				TimeLast = (dLastX / RelativeVel.x);
			}
		}
		if (Rect1.max.x < Rect2.min.x) {
			return 0;
		}
	}

	//Final check
	if (TimeFirst > TimeLast) {
		return false; //No collision
	}

	////////////////////
	///////Y-Axis///////
	////////////////////
	float dFirstY = Rect1.min.y - Rect2.max.y;
	float dLastY = Rect1.max.y - Rect2.min.y;
	//Time lesser than 0
	if (RelativeVel.x < 0) {
		//Case 1
		if (Rect1.min.y > Rect2.max.y) {
			return false;
		}
		//Case 4
		if (Rect1.max.y < Rect2.min.y) {
			if (dFirstY / RelativeVel.y > TimeFirst) {
				TimeFirst = dFirstY / RelativeVel.y;
			}
			if ((dLastY / RelativeVel.y) < TimeLast) {
				TimeLast = dLastY / RelativeVel.y;
			}
			
		}
	
	}
	if (RelativeVel.y > 0) {
		//Case 2
		if (Rect1.max.y > Rect2.min.y) {
			if ((dFirstY / RelativeVel.y) > TimeFirst) {
				TimeFirst = dFirstY / RelativeVel.y;
			}
			if ((dLastY / RelativeVel.y) > TimeLast) {
				TimeLast = dFirstY / RelativeVel.y;
			}
			
		}

		//Case3
		if (Rect1.max.y < Rect2.min.y) {
			return 0;
		}
	}

	//Final check
	if (TimeFirst > TimeLast) {
		return false; //No collision
	}

	std::cout << "dynamic collision!";
	return TimeFirst;

}