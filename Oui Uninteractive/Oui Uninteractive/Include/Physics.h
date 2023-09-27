#ifndef PHYSICS_H
#define PHYSICS_H

#include "ISystem.h"
#include "PhysicsBody.h"
#include <list>


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
	* @param float dt - delta time
	* @return void
	*************************************************************************/
	virtual void Update(float dt);
	/**************************************************************************
	* @brief Set the position of all object's Physics Body
	* @param Vec 2 pos - the position to be set to
	* @return void
	*************************************************************************/
	void SetPosition(Vec2 pos);
	/**************************************************************************
	* @brief Set the position of one object's Physics Body
	* @param Vec2 pos - the position to be set to
	* @param size_t ID - ID of object to set position
	* @return void
	*************************************************************************/
	void SetPosition(Vec2 pos, size_t ID);
	/**************************************************************************
	* @brief Set the velocity of all object's Physics Body
	* @param Vec 2 newVelocity - the velocity to be set to
	* @return void
	*************************************************************************/
	void SetVelocity(Vec2 vel);
	/**************************************************************************
	* @brief Set the velocity of one object's Physics Body
	* @param Vec 2 newVelocity - the velocity to be set to
	* @param size_t ID - ID of object to set position
	* @return void
	*************************************************************************/
	void SetVelocity(Vec2 vel, size_t ID);
	/**************************************************************************
	* @brief Set the rotation speed of all Physics Body
	* @param float rotSpeed - the rotation speed to be set to
	* @return void
	*************************************************************************/
	void SetRotationSpeed(float rotSpeed);
	/**************************************************************************
	* @brief Set the rotation speed of one object's Physics Body
	* @param float rotSpeed - the rotation speed to be set to
	* @return void
	*************************************************************************/
	void SetRotationSpeed(float rotSpeed, size_t ID);
	/**************************************************************************
	* @brief Set the current rotation speed of all Physics Body
	* @param float rotSpeed - the rotation speed to be set to
	* @return void
	*************************************************************************/
	void SetCurrentRotationSpeed(float rotSpeed);
	/**************************************************************************
	* @brief Set the current rotation speed of one object's Physics Body
	* @param float rotSpeed - the rotation speed to be set to
	* @return void
	*************************************************************************/
	void SetCurrentRotationSpeed(float rotSpeed, size_t ID);
	/**************************************************************************
	* @brief Set the direction of one object's Physics Body
	* @param Vec2 dir - the direction to be set to
	* @param size_t ID - ID of object to set direction
	* @return void
	*************************************************************************/
	void SetDirection(Vec2 dir, size_t ID);
	/**************************************************************************
	* @brief Helper function to move an object backwards
	* @param size_t ID - ID of object to move
	* @return void
	*************************************************************************/
	void MoveBackwards(size_t ID);
	/**************************************************************************
	* @brief Helper function to move an object forward
	* @param size_t ID - ID of object to move
	* @return void
	*************************************************************************/
	void MoveForward(size_t ID);
	/**************************************************************************
	* @brief Helper function to move an object left
	* @param size_t ID - ID of object to move
	* @return void
	*************************************************************************/
	void MoveLeft(size_t ID);
	/**************************************************************************
	* @brief Helper function to move an object right
	* @param size_t ID - ID of object to move
	* @return void
	*************************************************************************/
	void MoveRight(size_t ID);
	/**************************************************************************
	* @brief Calculate direction vector from angle of rotation
	* @param float angle - angle to convert to vector (in radians)
	* @return double
	*************************************************************************/
	Vec2 AngleToVec(float angle);
	//insert linked list of all physics body components
	std::map<size_t, PhysicsBody*> bodyList;
};
//Global pointer
extern Physics* physicsSys;

#endif
