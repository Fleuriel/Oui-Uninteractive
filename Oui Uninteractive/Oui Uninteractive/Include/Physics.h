#pragma once

#include "ISystem.h"
#include "PhysicsBody.h"
#include <list>
//Physics system should act on physics body component

class Physics : public ISystem{
	Physics();
	
	virtual void Update(float dt);
	void Initialize();
	

	//insert linked list of all physics body components
	std::list<PhysicsBody> bodyList;

//	void addForce(Vec2 force);
	//void setPosition(Vec2 pos);
	//void setVelocity(Vec2 vel);
};
extern Physics* physicsSys;
