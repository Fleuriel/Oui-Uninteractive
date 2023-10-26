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
bool CollisionMouseRect(Collider::AABB Rect1);

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
bool CollisionMovingRectRect(Collider::AABB Rect1, Collider::AABB Rect2, Vec2 Rect1Vel, Vec2 Rect2Vel);

#endif
