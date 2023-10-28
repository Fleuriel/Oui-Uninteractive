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
	
	
}
bool MovingPointRectCollision(Vec2 origin, Vec2 direction, Collider::AABB target, Vec2& contactPoint, Vec2& contactNormal, float& contactTime) {
	float tNearX = (target.min.x - origin.x) / direction.x;
	float tFarX = (target.max.x - origin.x) / direction.x;

	if (tNearX > tFarX) {
		std::swap(tNearX, tFarX);
	}

	float tNearY = (target.min.y - origin.y) / direction.y;
	float tFarY = (target.max.y - origin.y) / direction.y;

	if (tNearY > tFarY) {
		std::swap(tNearY, tFarY);
	}
	
	contactTime = std::max(tNearX, tNearY);
	float tFarthest = std::min(tFarX, tFarY);
	if (tFarthest < 0) {
		return false;
	}

	contactPoint = origin + (direction * contactTime);

	if (tNearX > tNearY) {
		if (direction.x > 0) {
			contactNormal = Vec2(-1, 0);
		}
		else {
			contactNormal = Vec2(1, 0);
		}
	}
	else if (tNearY > tNearX) {
		if (direction.y > 0) {
			contactNormal = Vec2(0, -1);
		}
		else {
			contactNormal = Vec2(0, 1);
		}
	}
	return true;
}
bool CollisionMovingRectRect(Collider::AABB A, Collider::AABB B, Vec2 AVel, Vec2 BVel, float& contactTime, Vec2& normal, Vec2& contactPoint, float dt) {
		
	if (AVel.x == 0 && AVel.y == 0) {
		return false;
	}
	Collider expanded_target;
	expanded_target.boundingbox->center = B.center;
	expanded_target.boundingbox->max = Vec2(B.max.x + A.txPtr->scale / 2, B.max.y + A.txPtr->scale / 2);
	expanded_target.boundingbox->min = Vec2(B.min.x - A.txPtr->scale / 2, B.min.y - A.txPtr->scale / 2);
	

	if (MovingPointRectCollision(A.center, AVel * dt, *(expanded_target.boundingbox), contactPoint, normal, contactTime)) {
		if (contactTime <= 1.0f) {
			return true;
		}
	}
	return false;
		////Velocity variables
		//Vec2 RelativeVel = BVel - AVel;
		//float TimeFirst{ 0 };
		//
		//bool alreadyOverlapX = false;
		//float dFirstX = A.min.x - B.max.x;
		//float test = A.min.x - B.min.x;
		//// A moving Left
		//if (abs(dFirstX) < abs(test)) {
		//	normalX = -1;
		//	normalY = 0;
		//	//A moving Left into B
		//	if (RelativeVel.x < 0) {
		//		
		//		TimeFirst = -dFirstX / (RelativeVel.x * GetDT());
		//	}
		//	//B moving into A
		//	if (RelativeVel.x > 0) {
		//		TimeFirst = dFirstX / (RelativeVel.x * GetDT()) ;
		//	}
		//}
		//else if (abs(dFirstX) > abs(test)) {
		//	//A moving Right
		//	float test2 = A.max.x - B.min.x;
		//	if (RelativeVel.x < 0) {
		//		//B moving Right onto A
		//		TimeFirst = test2 / (RelativeVel.x * GetDT());

		//	}
		//	if (RelativeVel.x > 0) {
		//		TimeFirst = -test2 / (RelativeVel.x * GetDT());
		//	}
		//}

		//if ((A.min.x < B.max.x) && (A.max.x > B.min.x)){
		//	alreadyOverlapX = true;
		//}
		////Decide which side the object is coming from
		//float dFirstY = A.max.y - B.min.y;
		//float test3 = A.max.y - B.max.y;
		//bool alreadyOverlapY = false;
		//float TimeFirstY = 0.0f;

		//if (abs(dFirstY) < abs(test3)) {
		//	
		//	//A moving Upwards
		//	if (RelativeVel.y > 0) {
		//		TimeFirstY = -dFirstY / (RelativeVel.y * GetDT());
		//	}
		//	// if B is faster
		//	if (RelativeVel.y < 0) {
		//		TimeFirstY = dFirstY / (RelativeVel.y * GetDT());
		//	}
		//}
		//else if (abs(dFirstY) > abs(test3)) {
		//	float test4 = A.min.y - B.max.y;
		//	if (RelativeVel.y > 0) {
		//		TimeFirstY = -test4 / (RelativeVel.y * GetDT());
		//	}
		//	if (RelativeVel.y < 0) {
		//		//A moving down into B
		//		TimeFirstY = test4 / (RelativeVel.y * GetDT());
		//	}

		//}
		////check if already overlapping y axis
		//if ((A.min.y < B.max.y) && (B.min.y < A.max.y) ){
		//	alreadyOverlapY = true;
		//} 

		//if (alreadyOverlapY && (TimeFirst > 0.f && TimeFirst < 1.f)) {	
		//	tFirst = TimeFirst;
		//	return 1;
		//}
		//if (alreadyOverlapX && (TimeFirstY > 0.f && TimeFirstY < 1.f)) {
		//	tFirst = TimeFirstY;
		//	return 1;
		//}
		//else {
		//	return 0;
		//}
		//

}