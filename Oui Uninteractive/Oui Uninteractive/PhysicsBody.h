#pragma once
#include "IComponent.h"
#include "Physics.h"

class PhysicsBody : public IComponent {
public:
	PhysicsBody();
	//~PhysicsBody();

	virtual void Initialize();
	Vec2 position;
	Vec2 velocity;
};