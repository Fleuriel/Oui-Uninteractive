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

#include <bitset>
#include "OpenGLApplication.h"


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
	* @brief Helper function to move an object backwards
	* @param ID - ID of object to move
	* @return void
	*************************************************************************/
	void MoveBackwards(size_t ID);
	/**************************************************************************
	* @brief Helper function to move an object forward
	* @param ID - ID of object to move
	* @return void
	*************************************************************************/
	void MoveForward(size_t ID);
	/**************************************************************************
	* @brief Helper function to move an object left
	* @param ID - ID of object to move
	* @return void
	*************************************************************************/
	void MoveLeft(size_t ID);
	/**************************************************************************
	* @brief Helper function to move an object right
	* @param ID - ID of object to move
	* @return void
	*************************************************************************/
	void MoveRight(size_t ID);
	/**************************************************************************
	* @brief Calculate direction vector from angle of rotation
	* @param angle - angle to convert to vector (in radians)
	* @return double
	*************************************************************************/
	Vec2 AngleToVec(float angle);
	void CapVelocity(Vec2 originalVelocity, Vec2& bodyVelocity);
	//insert linked list of all physics body components
	std::map<size_t, PhysicsBody*> bodyList;

	float maxVelocity = 3000.f

	double accumulatedTime = 0.0;//one time definition
	int currentNumberOfSteps = 0;
	const double fixedDeltaTime = 1.0 / 60;

};
//Global pointer
extern Physics* physicsSys;

#endif
