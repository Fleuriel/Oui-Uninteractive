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
		Vector2D direction;
		direction = Rect2.center - Rect1.center;
		//std::cout << "Direction X: " << direction.x << "Direction Y: " << direction.y << "\n";
		//std::cout << "Direction: " << direction.center.x << " " << direction.center.y;
		
		Vector2D Rect1norm;
		Vector2DNormalize(Rect1norm, direction);

		if (Vector2DDotProduct(direction, Rect1norm) < 0.f) {
			Rect1norm = -Rect1norm;
			physicsSys->bodyList[0]->velocity = Rect1norm;
		}
		
		
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
bool CollisionMovingRectRect(float r1x = 1, float r1y = 2, float r2x = 3, float r2y = 4, 
							 float r1velocityX = 5, float r1velocityY = 6, float r2velocityX = 7, float r2velocityY = 8,
							 float s1 = 9, float s2 = 10) {
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
	if (RelativeVel_X < 0) {
		//Case 1
		if (leftA > rightB) {
			return false;
		}

		//Case 4
		if (rightA < leftB) {
			TimeFirst = std::max(((rightA - leftB) / RelativeVel_X), TimeFirst);
		}
		if (leftA < rightB) {
			TimeLast = std::min(((leftA - rightB) / RelativeVel_X), TimeLast);
		}
	}

	//Time more than 0
	if (RelativeVel_X > 0) {
		//Case 2
		if (leftA > rightB) {
			TimeFirst = std::max(((leftA - rightB) / RelativeVel_X), TimeFirst);
		}
		if (rightA > leftB) {
			TimeLast = std::min(((rightA - leftB) / RelativeVel_X), TimeLast);
		}

		//Case 3
		if (rightA < leftB) {
			return false;
		}
	}

	//Final check
	if (TimeFirst > TimeLast) {
		return false; //No collision
	}

	////////////////////
	///////Y-Axis///////
	////////////////////
	
	//Time lesser than 0
	if (RelativeVel_Y < 0) {
		//Case 1
		if (bottomA > topB) {
			return false;
		}
		//Case 4
		if (topA < bottomB) {
			TimeFirst = std::max(((topA - bottomB) / RelativeVel_Y), TimeFirst);
		}
		if (bottomA < topB) {
			TimeLast = std::min(((bottomA - topB) / RelativeVel_Y), TimeLast);
		}
	}
	if (RelativeVel_Y > 0) {
		//Case 2
		if (bottomA > topB) {
			TimeFirst = std::max(((bottomA - topB) / RelativeVel_Y), TimeFirst);
		}
		if (topA > bottomB) {
			TimeLast = std::min(((topA - bottomB) / RelativeVel_Y), TimeLast);
		}

		//Case 3
		if (topA < bottomB) {
			return false;
		}
	}

	//Final check
	if (TimeFirst > TimeLast) {
		return false; //No collision
	}

	return false;
}