#pragma once

#ifndef COLLIDERSYS_H
#define COLLIDERSYS_H


#define HEIGHT 4
#define WIDTH 4
#include "Collider.h"
#include "Collision.h"
#include "ISystem.h"
#include "ObjectFactory.h"
#include "ComponentFactory.h"
#include "Editor.h"
#include <map>
using bitArray = std::bitset<3000>;
class ColliderSystem : public ISystem {
public:
	ColliderSystem();
	virtual void Initialize();
	virtual void Update(float dt);
	std::map<size_t, Collider*> colliderMap;
	std::vector <std::set<int>> collisionData;
	void BroadPhase();
	bitArray rowsBitArray[WIDTH];
	bitArray colBitArray[HEIGHT];
	int cellWidth;
	int cellHeight;
};
extern ColliderSystem* colliderSys;
#endif