#pragma once

#include "ISystem.h"
#include "PhysicsBody.h"
#include <list>
//Physics system should act on physics body component

class Physics : public ISystem{
	void addForce(Vec2 force);
	void setPosition(Vec2 pos);
	//gonna add an overload to set a particular object
	// void setPosition(Vec2 pos, objectID ID)
	//void setVelocity(Vec2 vel);
public:
	Physics();

	virtual void Update(float dt);
	void Initialize();

	//insert linked list of all physics body components
	std::list<PhysicsBody*> bodyList;

};
extern Physics* physicsSys;
