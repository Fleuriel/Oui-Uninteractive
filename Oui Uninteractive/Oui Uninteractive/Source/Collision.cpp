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
bool CollisionMouseRect(Collider::AABB Rect1, int mouseX, int mouseY) {

	if ((Rect1.max.x > mouseX &&
		Rect1.max.y > mouseY) &&
		(mouseX > Rect1.min.x &&
			mouseY > Rect1.min.y)){
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
	float distanceXEntry = 0;
	float distanceYEntry = 0;

	bool Xinitialized = false;
	bool Yinitialized = false;

	if (Rect1Vel.x < 0) {
		Xinitialized = true;
		distanceXEntry = Rect2->max.x - Rect1->min.x;
	}
	else if (Rect1Vel.x > 0) {
		Xinitialized = true;
		distanceXEntry = Rect2->min.x - Rect1->max.x;
	}
	
	if (Rect1Vel.y < 0) {
		Yinitialized = true;
		distanceYEntry = Rect2->max.y - Rect1->min.y;
	}
	else if (Rect1Vel.y > 0){
		Yinitialized = true;
		distanceYEntry = Rect2->min.y - Rect1->max.y;
	}
	if (Xinitialized == false){
		if (distanceYEntry < 0) {
			normalY = 1;
			return distanceYEntry;
		}
		else {
			normalY = -1;
			return -distanceYEntry;
		}
	}
	if (Yinitialized == false) {
		if (distanceXEntry < 0) {
			normalX = 1;
			return distanceXEntry;
		}
		else {
			normalX = -1;
			return -distanceXEntry;
		}
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
	}
}
bool MovingPointRectCollision(Vec2 origin, Vec2 direction, Collider::AABB target, Vec2& contactNormal, float& contactTime) {
	float tNearX = (target.min.x - origin.x) / direction.x;
	float tFarX = (target.max.x - origin.x) / direction.x;
	
	if (direction.x == 0) {
		if ((target.min.x - origin.x) >= 0) {
			tNearX = std::numeric_limits<float>::infinity();

		}
		if ((target.min.x - origin.x) < 0) {
			tNearX = -std::numeric_limits<float>::infinity();
		}

		if ((target.max.x - origin.x) > 0) {
			tFarX = std::numeric_limits<float>::infinity();
		}
		if ((target.max.x - origin.x) <= 0) {
			tFarX = -std::numeric_limits<float>::infinity();
		}
	}

	if (tNearX > tFarX) {
		std::swap(tNearX, tFarX);
	}
	float tNearY = (target.min.y - origin.y) / direction.y;
	float tFarY = (target.max.y - origin.y) / direction.y;

	if (direction.y == 0) {
		if ((target.min.y - origin.y) >= 0) {
			tNearY = std::numeric_limits<float>::infinity();
		}
		if ((target.min.y - origin.y) < 0) {
			tNearY = -std::numeric_limits<float>::infinity();
		}
		if ((target.max.y - origin.y) > 0) {
			tFarY = std::numeric_limits<float>::infinity();
		}
		if ((target.max.y - origin.y) <= 0) {
			tFarY = -std::numeric_limits<float>::infinity();
		}
	}
	if (tNearY > tFarY) {
		std::swap(tNearY, tFarY);
	}
	
	contactTime = std::max(tNearX, tNearY);
	float tFarthest = std::min(tFarX, tFarY);
	if (tFarthest < 0) {
		return false;
	}


	if (tNearX > tNearY) {

		if (abs(target.min.x - origin.x) < abs(target.max.x - origin.x)) {
			contactNormal = Vec2(-1, 0);
		}
		else {
			contactNormal = Vec2(1, 0);
		}
	}
	else if (tNearY > tNearX) {
		if (abs(target.min.y - origin.y) < abs(target.max.y - origin.y)) {
			contactNormal = Vec2(0, -1);
		}
		else {
			contactNormal = Vec2(0, 1);
		}
	}
	return true;
}
bool CollisionMovingRectRect(Collider::AABB A, Collider::AABB B, Vec2 relativeVel, float& contactTime, Vec2& normal, float dt, Vec2 AVel) {
	if ((relativeVel.x == 0 && relativeVel.y == 0)) {
		return false;
	}
	Collider expanded_target;
	expanded_target.boundingbox->center = B.center;
	expanded_target.boundingbox->max = Vec2(B.max.x + A.txPtr->scale / 2, B.max.y + A.txPtr->scale / 2);
	expanded_target.boundingbox->min = Vec2(B.min.x - A.txPtr->scale / 2, B.min.y - A.txPtr->scale / 2);
	if (MovingPointRectCollision(A.center, relativeVel * dt, *(expanded_target.boundingbox), normal, contactTime)) {
		if (contactTime < 0.f) {
			if (Vector2DDotProduct(AVel, normal) < 0) {
				contactTime = 0.f;
				return true;
			}
		}
		if (contactTime <= 1.0f && contactTime >= 0.f) {
			return true;
		}
	}
	return false;
		

}