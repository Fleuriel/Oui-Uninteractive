#pragma once

#include "ISystem.h"
#include "PhysicsBody.h"
#include <list>
//Physics system should act on physics body component

class Physics : public ISystem{
public:
	void addForce(Vec2 force);
	void setPosition(Vec2 pos);
	void setPosition(Vec2 pos, size_t ID);
	void setVelocity(Vec2 vel);
	void setVelocity(Vec2 vel, size_t ID);

	Physics();

	virtual void Update(float dt);
	void Initialize();

	//insert linked list of all physics body components
	std::vector<PhysicsBody*> bodyList;

};
extern Physics* physicsSys;
