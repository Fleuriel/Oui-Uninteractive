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
			Vector2DNormalize(body->direction, body->direction + AngleToVec(body->txPtr->rotation * (static_cast<float>(M_PI) / 180.0f)));
			
			//Check update

			//calculate physics
			//Direction
			Vec2 normalizedVel = Vec2(0, 0);
			Vector2DNormalize(normalizedVel, body->velocity);
			Vec2 summedForce = body->forceManager.CalculateResultantForce();
			body->acceleration = (summedForce) * body->mass;
			/*
			if (body->GetOwner()->GetGameObjectID() == 0) {
				std::cout << "Acceleration: " << body->acceleration.x << " : " << body->acceleration.y << "\n";
			}*/
			//Velocity
			Vec2 originalVelocity = body->velocity;
			Collider* collider = GET_COMPONENT(body->GetOwner(), Collider, ComponentType::COLLIDER);
			//body->velocity = body->velocity + body->acceleration * GetDT() * collider->contactTime;//* sysManager->fixedDeltaTime;
			Vec2 previousVelocity = body->velocity;
			if (collider != nullptr) {

				body->velocity = body->velocity * (collider->contactTime) + body->acceleration * static_cast<float>(sysManager->fixedDeltaTime);//GetDT();//* sysManager->fixedDeltaTime;
			}
			else {
				body->velocity = body->velocity + body->acceleration * static_cast<float>(sysManager->fixedDeltaTime);
			}
			
			
			CapVelocity(originalVelocity, body->velocity);
			
			//Position	
			body->txPtr->previousPosition = body->txPtr->position;

			body->txPtr->position = body->txPtr->position + (body->velocity * static_cast<float>(sysManager->fixedDeltaTime));//* sysManager->fixedDeltaTime;
			
			//Rotation
			body->txPtr->rotation = body->txPtr->rotation + body->currentRotationSpeed * dt;
			if (body->txPtr->rotation >= 360.0f || body->txPtr->rotation <= -360.0f)
				body->txPtr->rotation = 0.0f;
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

void Physics::CollisionResponse(CollisionMessage* msg) {
	//std::cout << "Collision detected between " << msg->GetFirstCollider()->GetOwner()->GetName() << " (x,y): "<< msg->GetFirstCollider()->boundingbox->center.x << ", " << msg->GetFirstCollider()->boundingbox->center.y;
	//std::cout << " and " << msg->GetSecondCollider()->GetOwner()->GetName() << "(x, y): " << msg->GetSecondCollider()->boundingbox->center.x << ", " << msg->GetSecondCollider()->boundingbox->center.y << std::endl;

	float halfDepth = msg->GetDepth() / 2;
	Vec2 dir = msg->GetSecondCollider()->boundingbox->center - msg->GetFirstCollider()->boundingbox->center;
	if (Vector2DDotProduct(dir, msg->GetContactNormal()) < 0.f) {
	//	normal = -normal;
		msg->SetContactNormal(-msg->GetContactNormal());
	}

	//coll response
	Vec2 penetration = msg->GetContactNormal() * halfDepth;

//	PhysicsBody* pBody2 = GET_COMPONENT(body2->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
	PhysicsBody* pBody1 = physicsSys->bodyList[msg->GetFirstCollider()->GetOwner()->GetGameObjectID()];
	PhysicsBody* pBody2 = physicsSys->bodyList[msg->GetSecondCollider()->GetOwner()->GetGameObjectID()];

	if (pBody2->isStatic) {
		//pBody1->txPtr->position += msg->GetContactNormal() * msg->GetDepth();
		pBody1->velocity += msg->GetContactNormal() * msg->GetDepth();// * msg->GetFirstCollider()->contactTime;
	}
	else if (pBody1->isStatic) {
		//pBody2->txPtr->position += (-msg->GetContactNormal()) * msg->GetDepth();
		pBody2->velocity += msg->GetContactNormal() * msg->GetDepth();//* msg->GetFirstCollider()->contactTime;
	
	}
	else {
		pBody1->velocity += msg->GetContactNormal() * msg->GetDepth() / 2;// *msg->GetFirstCollider()->contactTime;
		pBody2->velocity -= msg->GetContactNormal() * msg->GetDepth() / 2; // *msg->GetFirstCollider()->contactTime;
		//pBody1->forceManager.ApplyToForce(normal, depth / 2, 0.05f, FORCE_INDEX::EXTERNAL);
		//pBody1->txPtr->position += msg->GetContactNormal() * (msg->GetDepth() / 2);
		//pBody2->forceManager.ApplyToForce(-normal, depth / 2, 0.05f, FORCE_INDEX::EXTERNAL);
		//pBody2->txPtr->position += (-msg->GetContactNormal() * (msg->GetDepth() / 2));
	}



}







