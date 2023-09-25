#pragma once

#include "ISystem.h"
#include "PhysicsBody.h"
#include <list>
//Physics system should act on physics body component

class Physics : public ISystem{
public:
	/**************************************************************************
	* @brief Default constructor for Physics System
	*************************************************************************/
	Physics();
	void AddForce(Vec2 force);
	void SetPosition(Vec2 pos);
	void SetPosition(Vec2 pos, size_t ID);
	void SetVelocity(Vec2 vel);
	void SetVelocity(Vec2 vel, size_t ID);
	void SetRotationSpeed(float rotSpeed);
	void SetRotationSpeed(float rotSpeed, size_t ID);
	void SetCurrentRotationSpeed(float rotSpeed);
	void SetCurrentRotationSpeed(float rotSpeed, size_t ID);
	void SetDirection(Vec2 dir, size_t ID);
	

	virtual void Update(float dt);
	void Initialize();
	void MoveBackwards(size_t ID);
	void MoveForward(size_t ID);
	void MoveLeft(size_t ID);
	void MoveRight(size_t ID);
	Vec2 AngleToVec(float angle);
	//insert linked list of all physics body components
	std::vector<PhysicsBody*> bodyList;

};
extern Physics* physicsSys;
