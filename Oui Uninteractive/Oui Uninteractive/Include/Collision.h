#pragma once
#include <CoordinateSystem.h>



bool CollisionStaticCircleCircle(Coordinates Coords1, Coordinates Coords2, float r1, float r2);
bool CollisionStaticDynamicRectRect(float r1x, float r1y, float r2x,float r2y, float s1, float s2);
bool CollisionMovingRectRect(float r1x, float r1y, float r2x, float r2y,
	float r1velocityX, float r1velocityY, float r2velocityX, float r2velocityY,
	float s1, float s2);