#pragma once
#include "ISystem.h"
#include "IComponent.h"
#include "Vector2D.h"

//Physics system should act on physics body component
class Physics : public ISystem{
	Physics();
	
	virtual void Update(float dt);
	void Initialize();
	

	//linked list of all physics body components

//	void addForce(Vec2 force);
	//void setPosition(Vec2 pos);
	//void setVelocity(Vec2 vel);
};
extern Physics* physicSys;