/**************************************************************************
 * @file		  Collision.h
 * @author		  QUEK Cheng Kwang Emery
 * @par DP email: c.quek@digipen.edu
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-25-2023
 * @brief		  This is a header file for collision.cpp that declares
 *				  the function names and is to be included by other files
 *				  that wishes to access collision functions.
 *************************************************************************/
#ifndef COLLISION_H
#define COLLISION_H

#include <CoordinateSystem.h>
#include "PhysicsBody.h"
#include "Collider.h"
#include <cmath>
#include "Vector2D.h"
#include "GameStateManager.h"
#include "Physics.h"
#include "PhysicsBody.h"

 /**************************************************************************
  * @brief Check for collision for mouse and rectangle
  *
  * This function returns true or false depending on whether collision is
  * detected or not
  *
  * @param AABB Rect1 The Coordinates (x,y) of the rectangle
  *************************************************************************/
bool CollisionMouseRect(Collider::AABB Rect1, float mouseX, float mouseY);
bool CollisionMouseRect(Vec2 objCenter, float objScaleX, float objScaleY, float mouseX, float mouseY);
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
bool CollisionMouseCircle(Coordinates Coords1, float r1);

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
bool CollisionStaticCircleCircle(Coordinates Coords1, Coordinates Coords2, float r1, float r2);

/**************************************************************************
 * @brief Check for collision between static-dynamic rectangles
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param Rect1 Coordinates of the first rectangle
 * @param Rect2 Coordinates of the second rectangle
 *************************************************************************/
bool CollisionStaticDynamicRectRect(Collider::AABB Rect1, Collider::AABB Rect2);

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
bool CollisionMovingRectRect(Collider::AABB A, Collider::AABB B, Vec2 relativeVel, float& contactTime, Vec2& normal, float dt, Vec2 AVel);
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
bool MovingPointRectCollision(Vec2 origin, Vec2 direction, Collider::AABB target, Vec2& contactNormal, float& contactTime);

/**************************************************************************
 * @brief Collision detection whether a point is within a rotated rectangle
 *
 * This function returns true or false depending on whether collision is
 * detected or not
 *
 * @param objCenter	Point representing center of the object
 * @param objScaleX	X Scale of Rectangle
 * @param objScaleY	Y Scale of Rectangle
 * @param mouseX	X position of mouse
 * @param mouseX	Y position of mouse
 * @param angle		Rotation of Rect
 *************************************************************************/
bool CollisionPointRotateRect(Vec2 objCenter, float objScaleX, float objScaleY, float mouseX, float mouseY, float angle);
#endif
