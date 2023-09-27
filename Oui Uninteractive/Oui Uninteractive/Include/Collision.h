#ifndef COLLISION_H
#define COLLISION_H

/**************************************************************************
 * @file		  Collision.h
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-25-2023
 * @brief		  This is a header file for collision.cpp that declares
 *				  the function names and is to be included by other files
 *				  that wishes to access collision functions.
 *************************************************************************/
#pragma once
#include <CoordinateSystem.h>
#include "PhysicsBody.h"

bool CollisionStaticCircleCircle(Coordinates Coords1, Coordinates Coords2, float r1, float r2);
bool CollisionStaticDynamicRectRect(AABB Rect1, AABB Rect2);
bool CollisionMovingRectRect(float r1x, float r1y, float r2x, float r2y,
	float r1velocityX, float r1velocityY, float r2velocityX, float r2velocityY,
	float s1, float s2);

#endif
