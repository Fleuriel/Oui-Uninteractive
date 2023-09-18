#pragma once
#include "IComponent.h"
#include "Transform.h"
#include "Vector2D.h"
#include "GameObject.h"

class PhysicsBody : public IComponent {
public:
	PhysicsBody();
	//~PhysicsBody();

	virtual void Initialize();
	virtual void Serialize(std::string str, JsonSerializer serializer);
	Vec2 position;
	Vec2 velocity;
	Vec2 accumulatedForce;
	Vec2 prevPosition;
	Vec2 acceleration;

	Transform* txPtr; //Ptr to transform component for each physics body;
					  

	bool isStatic; // flag for engine to ignore objects that we won't move.
};