#pragma once

#ifndef COLLIDERSYS_H
#define COLLIDERSYS_H
#include "Collider.h"
#include "ISystem.h"
#include "ObjectFactory.h"
#include "ComponentFactory.h"
#include <map>

class ColliderSystem : public ISystem {
public:
	ColliderSystem();
	virtual void Initialize();
	virtual void Update(float dt);
	std::map<size_t, Collider*> colliderMap;
};
extern ColliderSystem* colliderSys;
#endif