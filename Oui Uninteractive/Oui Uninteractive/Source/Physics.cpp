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

#include "Physics.h"
#include "ColliderSystem.h"


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

	// Message System
	AddMessageHandler("MSG_COLLISION", (MessageHandler)CollisionResponse);
}
/**************************************************************************
* @brief Update Function of the Physics System
* @param dt - delta time
* @return void
*************************************************************************/
void Physics::Update(float dt) {
	// Start time profiling for physics system
	TimeProfiler profiler(Editor::timeRecorder.physicsTime);
	for (int step = 0; step < sysManager->currentNumberOfSteps; step++) {
	
		std::map<size_t, PhysicsBody*>::iterator it = bodyList.begin();
		for (; it != bodyList.end(); it++) {
			
			PhysicsBody* body = it->second;
			if (body->isStatic) {
				continue;
			}
			if (body->txPtr != nullptr) {
				Vector2DNormalize(body->direction, body->direction + AngleToVec(body->txPtr->rotation * (static_cast<float>(M_PI) / 180.0f)));
			}
			//Check update
			//calculate physics
			//Direction
			
			Vec2 summedForce = body->forceManager.CalculateResultantForce();
			body->acceleration = (summedForce) * body->mass;

			//Velocity
			Vec2 originalVelocity = body->velocity;
			Collider* collider = GET_COMPONENT(body->GetOwner(), Collider, ComponentType::COLLIDER);
			Vec2 previousVelocity = body->velocity;
			if (collider != nullptr) {
				if (body->GetOwner()->GetName() == "JSONPlayer") {
					std::cout << collider->contactTime << "\n";
					if (collider->contactTime == 0) {
						int test = 0;
					}
				}
				body->velocity = (body->velocity + body->acceleration * static_cast<float>(sysManager->fixedDeltaTime)) * (collider->contactTime);//GetDT();//* sysManager->fixedDeltaTime;
				
			}
			else {
				body->velocity = body->velocity + body->acceleration * static_cast<float>(sysManager->fixedDeltaTime);
			}
			
			
			CapVelocity(originalVelocity, body->velocity);
			if (body->txPtr != nullptr) {
				//Position	
				body->txPtr->previousPosition = body->txPtr->position;

				body->txPtr->position = body->txPtr->position + (body->velocity * static_cast<float>(sysManager->fixedDeltaTime));//* sysManager->fixedDeltaTime;

				//Rotation
				body->txPtr->rotation = body->txPtr->rotation + body->currentRotationSpeed * dt;
				if (body->txPtr->rotation >= 360.0f || body->txPtr->rotation <= -360.0f)
					body->txPtr->rotation = 0.0f;
			}
			Vec2 normalizedVel = Vec2(0, 0);
			Vector2DNormalize(normalizedVel, body->velocity);
			body->forceManager.forceVec[FORCE_INDEX::FRICTION]->direction = -normalizedVel;
			body->forceManager.Update(static_cast<float>(sysManager->fixedDeltaTime));
		
		}
	}
	

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
* @brief Calculate direction vector from angle of rotation
* @param angle - angle to convert to vector (in radians)
* @return double 
*************************************************************************/
Vec2 Physics::AngleToVec(float angle) {
	//angle should be in radians
	Vec2 dir = Vec2(-sinf(angle), cosf(angle));
	return dir;
}
/**************************************************************************
* @brief Calculate direction vector from angle of rotation
* @param Vec2 originalVelocity - velocity from previous frame
* @param Vec2 bodyVelocity - velocity in current frame
* @return void
*************************************************************************/
void Physics::CapVelocity(Vec2 originalVelocity, Vec2& bodyVelocity) {
	if (bodyVelocity.x > maxVelocity) {
		bodyVelocity.x = maxVelocity;
	}
	if (bodyVelocity.x < -maxVelocity) {
		bodyVelocity.x = -maxVelocity;
	}
	if (bodyVelocity.y > maxVelocity) {
		bodyVelocity.y = maxVelocity;
	}
	if (bodyVelocity.y < -maxVelocity) {
		bodyVelocity.y = -maxVelocity;
	}

	if (originalVelocity.x > 0 ) {
		if (bodyVelocity.x < 0) {
			bodyVelocity.x = 0;
		}
	}
	else if (originalVelocity.x < 0) {
		if (bodyVelocity.x > 0) {
			bodyVelocity.x = 0;
		}
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
/**************************************************************************
* @brief Collision Response Message
* @param CollisionMessage* - ptr to message object
* @return void
*************************************************************************/
void Physics::CollisionResponse(CollisionMessage* msg) {
	PhysicsBody* pBody1 = GET_COMPONENT(msg->GetFirstCollider()->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
	PhysicsBody* pBody2 = GET_COMPONENT(msg->GetSecondCollider()->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
	msg->GetFirstCollider()->contactTime = msg->GetFirstContactTime();
	msg->GetFirstCollider()->contactNormal = msg->GetContactNormal();
	msg->GetSecondCollider()->contactTime = msg->GetSecondContactTime();
	msg->GetSecondCollider()->contactNormal = msg->GetSecondContactNormal();

	pBody1->velocity = pBody1->velocity * (msg->GetFirstCollider()->contactTime) + (pBody1->forceManager.CalculateResultantForce() * pBody1->mass) * static_cast<float>(sysManager->fixedDeltaTime);
	pBody2->velocity = pBody2->velocity * (msg->GetSecondCollider()->contactTime) + (pBody2->forceManager.CalculateResultantForce() * pBody2->mass) * static_cast<float>(sysManager->fixedDeltaTime);
}







