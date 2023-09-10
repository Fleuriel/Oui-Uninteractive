#pragma once
#include "PhysicsHeaders.h"

class PhysicsBody : public IComponent {
public:
	PhysicsBody();
	//~PhysicsBody();

	virtual void Initialize();
	Vec2 position;
	Vec2 velocity;
	Vec2 accumulatedForce;
	Vec2 prevPosition;
	Vec2 acceleration;

	Transform* txPtr; //Ptr to transform component for each physics body;
					  

	bool isStatic; // flag for engine to ignore objects that we won't move.
};