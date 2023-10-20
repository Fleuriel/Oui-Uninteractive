/**************************************************************************
 * @file Physics.cpp
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 08-09-2023
 * @brief This file contains the definition of the Physics Class,
 *		  which handles all Physics calculations done on the Physics
 *		  Body component.
 *************************************************************************/
#include <iostream>
#include <algorithm>
#include <chrono>
#include "Physics.h"
#include "ComponentFactory.h"
#include "ObjectFactory.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Editor.h"
//initialize global pointer
Physics* physicsSys = nullptr;

/**************************************************************************
* @brief Default constructor for Physics System
*************************************************************************/
Physics::Physics() {
	if (physicsSys != nullptr) {
		//instantiate physics system
		return;
	}
	else {
		cellWidth = 0;
		cellHeight = 0;
		physicsSys = this;
	}
}
/**************************************************************************
* @brief Initializes the Physics System
* @return void
*************************************************************************/
void Physics::Initialize() {
	//Register Component creator of Body here
	
	ComponentFactory<PhysicsBody>* testPtr = new ComponentFactory<PhysicsBody>(ComponentType::PHYSICS_BODY);
	objectFactory->AddComponentFactory(ComponentType::PHYSICS_BODY, testPtr);
	//cellWidth = windowSize.first / WIDTH;
	//cellHeight = windowSize.second / HEIGHT;
}
/**************************************************************************
* @brief Update Function of the Physics System
* @param dt - delta time
* @return void
*************************************************************************/
void Physics::Update(float dt) {
	// Start time profiling for physics system
	TimeProfiler profiler(Editor::timeRecorder.physicsTime);
	//std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
	std::map<size_t, PhysicsBody*>::iterator it = bodyList.begin();
	std::map<size_t, PhysicsBody*>::iterator it2 = bodyList.begin();
	for (; it != bodyList.end(); it++) {
		PhysicsBody* body = it->second;
		if (body->isStatic) {
			continue;
		}
		Vector2DNormalize(body->direction, body->direction + AngleToVec(body->txPtr->rotation * (static_cast<float>(M_PI) / 180.0f)));
		body->forceManager.Update(dt);
		//Check update
		body->boundingbox->min = Vec2((-0.5f) * body->txPtr->scale + body->txPtr->position.x, (-0.5f) * body->txPtr->scale + body->txPtr->position.y);
		body->boundingbox->max = Vec2((0.5f) * body->txPtr->scale + body->txPtr->position.x, (0.5f) * body->txPtr->scale + body->txPtr->position.y);
		//calculate physics
		//Direction
		Vec2 normalizedVel = Vec2(0,0);
		Vector2DNormalize(normalizedVel, body->velocity);
		Vec2 summedForce = body->forceManager.CalculateResultantForce();
		body->acceleration = (summedForce - (body->frictionForce * normalizedVel)) * body->mass;
		/*
		if (body->GetOwner()->GetGameObjectID() == 0) {
			std::cout << "Acceleration: " << body->acceleration.x << " : " << body->acceleration.y << "\n";
		}*/
		//Velocity
		Vec2 originalVelocity = body->velocity;
		
		body->velocity = body->velocity + body->acceleration * dt;

		CapVelocity(originalVelocity, body->velocity);
		/*
		if (body->GetOwner()->GetGameObjectID() == 0) {
			std::cout << "velocity: " << body->velocity.x << " : " << body->velocity.y << "\n";
		}
		*/
		
		//Position
		body->txPtr->position = body->txPtr->position + body->velocity * dt;
		size_t test = body->GetOwner()->GetGameObjectID();
		
		//rowsBitArray[body->implicitGridPos.first].set(body->GetOwner()->GetGameObjectID(), 0);
		//colBitArray[body->implicitGridPos.second].set(body->GetOwner()->GetGameObjectID(), 0);
		/*Vec2 absPosition = Vec2(0, 0);
		
		absPosition.x = body->txPtr->position.x + (windowSize.first / 2.0f);
		absPosition.y = body->txPtr->position.y + (windowSize.second / 2.0f);
		
		body->implicitGridPos.first = absPosition.x / cellWidth; //which row
		body->implicitGridPos.second = absPosition.y / cellHeight; //which col

		rowsBitArray[body->implicitGridPos.first].set(test);
		colBitArray[body->implicitGridPos.second].set(test);
		*/
		//Just spins all other objects
		if (body->GetOwner()->GetGameObjectID() != 0) {
			body->currentRotationSpeed = body->rotationSpeed;
		}
		//Rotation
		body->txPtr->rotation = body->txPtr->rotation + body->currentRotationSpeed * dt;
		if (body->txPtr->rotation >= 360.0f || body->txPtr->rotation <= -360.0f)
			body->txPtr->rotation = 0.0f;
		//Collision Detection
		for (; it2 != bodyList.end(); it2++) {
			PhysicsBody* body2 = it2->second;
			if (body2->GetOwner()->GetGameObjectID() == body->GetOwner()->GetGameObjectID()) {
				continue;
			}
			CollisionStaticDynamicRectRect(*(body->boundingbox), *(body2->boundingbox));
		}
		//apply calculations to object
	//	body->txPtr->shape->Update(body->txPtr->position.x, body->txPtr->position.y, body->txPtr->scale, body->txPtr->scale, body->txPtr->rotation, true);
	}
	//std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<float, std::milli> duration = timeEnd - timeStart;
	//Editor::timeRecorder.physicsTime = duration.count();
}
/**************************************************************************
* @brief Set the position of all object's Physics Body
* @param pos - the position to be set to
* @return void
*************************************************************************/
void Physics::SetPosition(Vec2 pos) {
	std::map<size_t, PhysicsBody*>::iterator it = bodyList.begin();
	for (; it != bodyList.end(); it++) {
		PhysicsBody* body = it->second;
		body->txPtr->position = pos;
	}
}
/**************************************************************************
* @brief Set the position of one object's Physics Body
* @param pos - the position to be set to
* @param ID - ID of object to set position
* @return void
*************************************************************************/
void Physics::SetPosition(Vec2 pos, size_t ID) {
	
	if (bodyList.find(ID) != bodyList.end()) {
		bodyList.at(ID)->txPtr->position = pos;	
	}
}
/**************************************************************************
* @brief Set the velocity of all object's Physics Body
* @param newVelocity - the velocity to be set to
* @return void
*************************************************************************/
void Physics::SetVelocity(Vec2 newVelocity) {
	std::map<size_t, PhysicsBody*>::iterator it = bodyList.begin();
	for (; it != bodyList.end(); it++) {
		PhysicsBody* body = it->second;
		body->velocity = newVelocity;
	}
}
/**************************************************************************
* @brief Set the velocity of one object's Physics Body
* @param newVelocity - the velocity to be set to
* @param ID - ID of object to set position
* @return void
*************************************************************************/
void Physics::SetVelocity(Vec2 velocity, size_t ID) {
	if (bodyList.find(ID) != bodyList.end()) {
		bodyList.at(ID)->velocity = velocity;
	}
}
/**************************************************************************
* @brief Set the rotation speed of one object's Physics Body
* @param rotSpeed - the rotation speed to be set to
* @return void
*************************************************************************/
void Physics::SetRotationSpeed(float rotSpeed) {
	std::map<size_t, PhysicsBody*>::iterator it = bodyList.begin();
	for (; it != bodyList.end(); it++) {
		PhysicsBody* body = it->second;
		body->rotationSpeed = rotSpeed;
	}
}
/**************************************************************************
* @brief Set the rotation speed of one object's Physics Body
* @param rotSpeed - the rotation speed to be set to
* @param ID - ID of object to set rotation speed
* @return void
*************************************************************************/
void Physics::SetRotationSpeed(float rotSpeed, size_t ID) {
	if (bodyList.find(ID) != bodyList.end()) {
		bodyList.at(ID)->rotationSpeed = rotSpeed;
	}
}
/**************************************************************************
* @brief Set the current rotation speed of all Physics Body
* @param rotSpeed - the rotation speed to be set to
* @return void
*************************************************************************/
void Physics::SetCurrentRotationSpeed(float rotSpeed) {
	std::map<size_t, PhysicsBody*>::iterator it = bodyList.begin();
	for (; it != bodyList.end(); it++) {
		PhysicsBody* body = it->second;
		body->currentRotationSpeed = rotSpeed;
	}
}
/**************************************************************************
* @brief Set the current rotation speed of one object's Physics Body
* @param rotSpeed - the rotation speed to be set to
* @return void
*************************************************************************/
void Physics::SetCurrentRotationSpeed(float rotSpeed, size_t ID) {
	if (bodyList.find(ID) != bodyList.end()) {
		bodyList.at(ID)->currentRotationSpeed = rotSpeed;
	}
}
/**************************************************************************
* @brief Set the direction of one object's Physics Body
* @param Vec2 dir - the direction to be set to
* @param ID - ID of object to set direction
* @return void
*************************************************************************/
void Physics::SetDirection(Vec2 dir, size_t ID) {
	if (bodyList.find(ID) != bodyList.end()) {
		Vector2DNormalize(bodyList.at(ID)->direction, dir);
	}
}
/**************************************************************************
* @brief Helper function to move an object backwards
* @param ID - ID of object to move
* @return void
*************************************************************************/
void Physics::MoveBackwards(size_t ID) {
	if (bodyList.find(ID) != bodyList.end()) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(-bodyList.at(ID)->direction.x, -bodyList.at(ID)->direction.y);
	}
}
/**************************************************************************
* @brief Helper function to move an object forward
* @param ID - ID of object to move
* @return void
*************************************************************************/
void Physics::MoveForward(size_t ID) {
	if (bodyList.find(ID) != bodyList.end()) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(bodyList.at(ID)->direction.x, bodyList.at(ID)->direction.y);
	}
}
/**************************************************************************
* @brief Helper function to move an object left
* @param ID - ID of object to move
* @return void
*************************************************************************/
void Physics::MoveLeft(size_t ID) {
	if (bodyList.find(ID) != bodyList.end()) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(-bodyList.at(ID)->direction.x, bodyList.at(ID)->direction.y);
	}
}
/**************************************************************************
* @brief Helper function to move an object right
* @param ID - ID of object to move
* @return void
*************************************************************************/
void Physics::MoveRight(size_t ID) {
	if (bodyList.find(ID) != bodyList.end()) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(bodyList.at(ID)->direction.x, bodyList.at(ID)->direction.y);
	}
}
/**************************************************************************
* @brief Calculate direction vector from angle of rotation
* @param angle - angle to convert to vector (in radians)
* @return double 
*************************************************************************/
Vec2 Physics::AngleToVec(float angle) {
	//angle should be in radians
	Vec2 dir = Vec2(-sinf(angle), cosf(angle));
	return dir;
}
void Physics::CapVelocity(Vec2 originalVelocity, Vec2& bodyVelocity) {
	if (originalVelocity.x > 0) {
		if (bodyVelocity.x < 0) {
			bodyVelocity.x = 0;
		}
	}
	else if (originalVelocity.x < 0) {
		if (bodyVelocity.x > 0) {
			bodyVelocity.x = 0;
		}
	}

	
	if (bodyVelocity.x > 3000.f) {
		bodyVelocity.x = 3000.f;
	}
	if (bodyVelocity.x < -3000.f) {
		bodyVelocity.x = -3000.f;
	}
	if (bodyVelocity.y > 3000.f) {
		bodyVelocity.y = 3000.f;
	}
	if (bodyVelocity.y < -3000.f) {
		bodyVelocity.y = -3000.f;
	}
	


	if (originalVelocity.y < 0) {
		if (bodyVelocity.y > 0) {
			bodyVelocity.y = 0;
		}
	}
	else if (originalVelocity.y > 0) {
		if (bodyVelocity.y < 0) {
			bodyVelocity.y = 0;
		}
	}
}