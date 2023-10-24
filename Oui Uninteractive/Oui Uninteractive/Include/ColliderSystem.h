#pragma once

#ifndef COLLIDERSYS_H
#define COLLIDERSYS_H


#define HEIGHT 2
#define WIDTH 2
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

	void BroadPhase();
	bitArray rowsBitArray[WIDTH];
	bitArray colBitArray[HEIGHT];
};
extern ColliderSystem* colliderSys;
#endif