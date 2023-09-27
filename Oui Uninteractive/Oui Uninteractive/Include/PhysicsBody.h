#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "IComponent.h"
#include "Transform.h"
#include "Vector2D.h"
#include "GameObject.h"

class PhysicsBody;

class AABB {
public:
	Vec2 min, max;
	PhysicsBody* pointer;

	AABB() {
		pointer = nullptr;
	};

};

class PhysicsBody : public IComponent {
public:
	PhysicsBody();
	~PhysicsBody();

	virtual void Initialize();
	virtual void Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr);
	virtual PhysicsBody* Clone() const;
	float rotationSpeed;
	float speed;
	AABB* boundingbox;

	//Vec2 position;
	Vec2 velocity;
	float currentRotationSpeed;
	Vec2 accumulatedForce;
	Vec2 prevPosition;
	Vec2 acceleration;
	Vec2 direction;

	Transform* txPtr; //Ptr to transform component for each physics body

	bool isStatic; // flag for engine to ignore objects that we won't move.
};

#endif
