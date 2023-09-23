#pragma once
#include "IComponent.h"
#include "Transform.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Collision.h"

class PhysicsBody : public IComponent {
public:
	PhysicsBody();
	//~PhysicsBody();

	virtual void Initialize();
	virtual void Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr);
	Vec2 AngleToVec(float angle);
	float rotationSpeed;
	float speed;

	//Vec2 position;
	Vec2 velocity;
	Vec2 accumulatedForce;
	Vec2 prevPosition;
	Vec2 acceleration;
	Vec2 direction;

	Transform* txPtr; //Ptr to transform component for each physics body

	bool isStatic; // flag for engine to ignore objects that we won't move.
};


class PhysicsBody2 : public AABB {

	//X and Y coordinates taken from Coords?
	float min, max;
	
};