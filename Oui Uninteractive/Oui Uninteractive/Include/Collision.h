#pragma once
#include <CoordinateSystem.h>

class AABB {
public:
	float x, y;

};

bool CollisionStaticCircleCircle(Coordinates Coords1, Coordinates Coords2, float r1, float r2);
bool CollisionStaticRectRect(float r1x, float r1y, float r2x,float r2y, float s1, float s2);
bool CollisionMovingRectRect(float r1x, float r1y, float r2x, float r2y, float s1, float s2, float r1velocity, float r2velocity);