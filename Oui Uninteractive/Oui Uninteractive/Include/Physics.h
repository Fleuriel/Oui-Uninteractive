/**************************************************************************
 * @file Physics.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 08-09-2023
 * @brief This file contains the declaration of the Physics Class,
 *		  which handles all Physics calculations done on the Physics
 *		  Body component.
 *************************************************************************/
#ifndef PHYSICS_H
#define PHYSICS_H

#include "ISystem.h"
#include "PhysicsBody.h"
#include <list>
#include "SystemManager.h"
#include <bitset>
#include "OpenGLApplication.h"
#include "ComponentFactory.h"
#include "ObjectFactory.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Editor.h"
#include <iostream>
#include <algorithm>
#include <chrono>

class CollisionMessage : public IMessage {
private:
	//CollisionMessage
	Collider* firstCollider;
	Collider* secondCollider;
	float contactTime;
	Vec2 contactNormal;
	float secondContactTime;
	Vec2 secondContactNormal;

public:
	CollisionMessage(Collider* first, Collider* second, float newContTime, Vec2 newContactNorm, float newContTime2, Vec2 newContNorm2) : IMessage("MSG_COLLISION"), firstCollider(first), secondCollider(second),
		contactTime(newContTime), contactNormal(newContactNorm), secondContactTime(newContTime2), secondContactNormal(newContNorm2)
	{ }
	~CollisionMessage() {}

	Collider* GetFirstCollider() { return firstCollider; }
	Collider* GetSecondCollider() { return secondCollider; }
	float GetSecondContactTime() {
		return secondContactTime;
	}
	Vec2 GetSecondContactNormal() {
		return secondContactNormal;
	}
	float GetFirstContactTime() {
		return contactTime;
	}
	Vec2 GetContactNormal() {
		return contactNormal;
	}
	void SetContactNormal(Vec2 newNorm) {
		contactNormal = newNorm;
	}
};

class Physics : public ISystem{
public:
	/**************************************************************************
	* @brief Default constructor for Physics System
	*************************************************************************/
	Physics();
	/**************************************************************************
	* @brief Initializes the Physics System
	* @return void
	*************************************************************************/
	void Initialize();
	/**************************************************************************
	* @brief Update Function of the Physics System
	* @param dt - delta time
	* @return void
	*************************************************************************/
	virtual void Update(float dt);
	/**************************************************************************
	* @brief Set the position of all object's Physics Body
	* @param pos - the position to be set to
	* @return void
	*************************************************************************/
	void SetPosition(Vec2 pos);
	/**************************************************************************
	* @brief Set the position of one object's Physics Body
	* @param pos - the position to be set to
	* @param ID - ID of object to set position
	* @return void
	*************************************************************************/
	void SetPosition(Vec2 pos, size_t ID);
	/**************************************************************************
	* @brief Set the velocity of all object's Physics Body
	* @param newVelocity - the velocity to be set to
	* @return void
	*************************************************************************/
	void SetVelocity(Vec2 vel);
	/**************************************************************************
	* @brief Set the velocity of one object's Physics Body
	* @param newVelocity - the velocity to be set to
	* @param ID - ID of object to set position
	* @return void
	*************************************************************************/
	void SetVelocity(Vec2 vel, size_t ID);
	/**************************************************************************
	* @brief Set the rotation speed of all Physics Body
	* @param rotSpeed - the rotation speed to be set to
	* @return void
	*************************************************************************/
	void SetRotationSpeed(float rotSpeed);
	/**************************************************************************
	* @brief Set the rotation speed of one object's Physics Body
	* @param rotSpeed - the rotation speed to be set to
	* @return void
	*************************************************************************/
	void SetRotationSpeed(float rotSpeed, size_t ID);
	/**************************************************************************
	* @brief Set the current rotation speed of all Physics Body
	* @param rotSpeed - the rotation speed to be set to
	* @return void
	*************************************************************************/
	void SetCurrentRotationSpeed(float rotSpeed);
	/**************************************************************************
	* @brief Set the current rotation speed of one object's Physics Body
	* @param rotSpeed - the rotation speed to be set to
	* @return void
	*************************************************************************/
	void SetCurrentRotationSpeed(float rotSpeed, size_t ID);
	/**************************************************************************
	* @brief Set the direction of one object's Physics Body
	* @param dir - the direction to be set to
	* @param ID - ID of object to set direction
	* @return void
	*************************************************************************/
	void SetDirection(Vec2 dir, size_t ID);
	/**************************************************************************
	* @brief Calculate direction vector from angle of rotation
	* @param angle - angle to convert to vector (in radians)
	* @return double
	*************************************************************************/
	Vec2 AngleToVec(float angle);
	/**************************************************************************
	* @brief Calculate direction vector from angle of rotation
	* @param Vec2 originalVelocity - velocity from previous frame
	* @param Vec2 bodyVelocity - velocity in current frame
	* @return void
	*************************************************************************/
	void CapVelocity(Vec2 originalVelocity, Vec2& bodyVelocity);

	/**************************************************************************
	* @brief Collision Response Message
	* @param CollisionMessage* - ptr to message object
	* @return void
	*************************************************************************/
	static void CollisionResponse(CollisionMessage* msg);
	
	//insert linked list of all physics body components
	std::map<size_t, PhysicsBody*> bodyList;
	float maxVelocity = 1000.f;

	

};
//Global pointer
extern Physics* physicsSys;

#endif
