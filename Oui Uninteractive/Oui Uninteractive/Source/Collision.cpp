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
 * @param Rect1  The Coordinates (x,y) of the rectangle
 * @param mouseX Coordinate X value of mouse
 * @param mouseY Coordinate Y value of mouse
 *************************************************************************/
bool CollisionMouseRect(Collider::AABB Rect1, float mouseX, float mouseY) {

	//std::cout << "MOUSE: " << mouseX << '\t' << mouseY << '\t';
//	std::cout << Rect1.center.x << Rect1.center.y << '\n';

	//std::cout << "THE STUPID BOX: " << Rect1.min.x << '\t' << Rect1.min.y << "BIG\t" << Rect1.max.x << '\t' << Rect1.max.y << '\n';
	//std::cout <<" Center: " << Rect1.center.x << '\t' << Rect1.center.y << '\n';


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

bool CollisionMouseRect(Vec2 objCenter, float objScaleX, float objScaleY, float mouseX, float mouseY) {
	/*collider->boundingbox->min = Vec2((-0.5f) * collider->tx->scale.x + collider->tx->position.x, (-0.5f) * collider->tx->scale.y + collider->tx->position.y);
	collider->boundingbox->max = Vec2((0.5f) * collider->tx->scale.x + collider->tx->position.x, (0.5f) * collider->tx->scale.y + collider->tx->position.y);*/
	Vec2 max = Vec2((0.5f) * objScaleX + objCenter.x , (0.5f) * objScaleY + objCenter.y);
	Vec2 min = Vec2(-(0.5f)* objScaleX + objCenter.x , -(0.5f) * objScaleY + objCenter.y);

	if ((max.x > mouseX &&
		max.y > mouseY) &&
		(mouseX > min.x &&
			mouseY > min.y)) {
		return true;
	}
	else {
		return false;
	}
}
/**************************************************************************
 * @brief Check for collision for mouse and circle
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param Coords1 The coordinates (x,y) of the shape
 * @param r1	  The size of the shape
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
 * @param r1	  Radius of the first circle
 * @param r2	  Radius of the second circle
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
 * @param Rect1 Coordinates(x,y) of the first rectangle
 * @param Rect2 Coordinates(x,y) of the second rectangle
 *************************************************************************/
bool CollisionStaticDynamicRectRect(Collider::AABB Rect1, Collider::AABB Rect2) {
		if ((Rect1.max.x > Rect2.min.x  && 
			 Rect1.max.y > Rect2.min.y) &&
			(Rect2.max.x > Rect1.min.x  &&
			 Rect2.max.y > Rect1.min.y)) {

		return true;
		}
		else {
		return false;
		}
}

/**************************************************************************
 * @brief Whether a point moving in a specified direction will collide with
		  a rectangle (represented by an Axis-Aligned Bounding Box (AABB)).
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param origin		The starting point of the line coordinates(x,y)
 * @param direction		A vector to represent direction
 * @param target		The destination point of the line coordinates(x,y)
 * @param contactNormal The normal of a vector on the point of collision
 * @param contactTime	The time on the point of collision
 *************************************************************************/
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

/**************************************************************************
 * @brief  Collision detection function that checks for collisions between 
		   two rectangles (A and B) with relative motion
 *
 * @param A			  Coordinates(x,y) of the first object
 * @param B			  Coordinates(x,y) of the second object
 * @param relativeVel The velocity of an object with respect to another
 * @param contactTime The time on the point of collision
 * @param normal	  Normal of a vector
 * @param dt		  Delta time
 * @param AVel		  Velocity of the first object
 *************************************************************************/
bool CollisionMovingRectRect(Collider::AABB A, Collider::AABB B, Vec2 relativeVel, float& contactTime, Vec2& normal, float dt, Vec2 AVel) {
	if ((relativeVel.x == 0 && relativeVel.y == 0)) {
		return false;
	}
	Collider expanded_target;
	expanded_target.boundingbox->center = B.center;
	expanded_target.boundingbox->max = Vec2(B.max.x + A.txPtr->scale.x / 2, B.max.y + A.txPtr->scale.y / 2);
	expanded_target.boundingbox->min = Vec2(B.min.x - A.txPtr->scale.x / 2, B.min.y - A.txPtr->scale.y / 2);
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