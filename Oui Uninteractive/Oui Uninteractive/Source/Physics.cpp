#include "Physics.h"
#include "ComponentFactory.h"
#include "ObjectFactory.h"
#include "Vector2D.h"
#include <iostream>
#include <algorithm>
#include "Collision.h"
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
	ComponentFactory<Transform>* testPtr2 = new ComponentFactory<Transform>(ComponentType::TRANSFORM);
	objectFactory->AddComponentFactory(ComponentType::TRANSFORM, testPtr2);
}
/**************************************************************************
* @brief Update Function of the Physics System
* @param float dt - delta time
* @return void
*************************************************************************/
void Physics::Update(float dt) {
	std::map<size_t, PhysicsBody*>::iterator it = bodyList.begin();
	std::map<size_t, PhysicsBody*>::iterator it2 = bodyList.begin();
	for (; it != bodyList.end(); it++) {
		PhysicsBody* body = it->second;
		if (body->isStatic) {
			continue;
		}

		//Check update
		body->boundingbox->min = Vec2((-1 / 2.f) * body->txPtr->scale + body->txPtr->position.x, (-1 / 2.f) * body->txPtr->scale + body->txPtr->position.y);
		body->boundingbox->max = Vec2((1 / 2.f) * body->txPtr->scale + body->txPtr->position.x, (1 / 2.f) * body->txPtr->scale + body->txPtr->position.y);

		//calculate physics
		Vector2DNormalize(body->direction, body->direction + AngleToVec(body->txPtr->rotation * (M_PI / 180.f)));
		
		body->txPtr->position = body->txPtr->position + body->velocity * dt;

		body->velocity = body->velocity + body->acceleration * dt;
		if (body->GetOwner()->GetGameObjectID() != 0) {
			body->currentRotationSpeed = body->rotationSpeed;
		}
		body->txPtr->rotation = body->txPtr->rotation + body->currentRotationSpeed * dt;
		if (body->txPtr->rotation >= 360.0f || body->txPtr->rotation <= -360.0f)
			body->txPtr->rotation = 0.0f;
	

		//Test collision
		for (; it2 != bodyList.end(); it2++) {
			PhysicsBody* body2 = it2->second;
			if (body2->GetOwner()->GetGameObjectID() == body->GetOwner()->GetGameObjectID()) {
				continue;
			}
			CollisionStaticDynamicRectRect(*(body->boundingbox), *(body2->boundingbox));
		}


		//apply to object
		body->txPtr->shape->Update(body->txPtr->position.x, body->txPtr->position.y, body->txPtr->scale, body->txPtr->rotation, true);	
	}

}
/**************************************************************************
* @brief Add force to all object's Physics Body
* @param Vec 2 force - force to be added to object
* @return void
*************************************************************************/
void Physics::AddForce(Vec2 force) {
	std::map<size_t, PhysicsBody*>::iterator it = bodyList.begin();
	for (; it != bodyList.end(); it++) {
		PhysicsBody* body = it->second;
		body->accumulatedForce += force;
	}
}
/**************************************************************************
* @brief Set the position of all object's Physics Body
* @param Vec 2 pos - the position to be set to
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
* @param Vec2 pos - the position to be set to
* @param size_t ID - ID of object to set position
* @return void
*************************************************************************/
void Physics::SetPosition(Vec2 pos, size_t ID) {
	
	if (objectFactory->GetGameObjectByID(ID) != nullptr &&
		objectFactory->GetGameObjectByID(ID)->Has(ComponentType::PHYSICS_BODY) != -1) {
		bodyList.at(ID)->txPtr->position = pos;	
	}
}
/**************************************************************************
* @brief Set the velocity of all object's Physics Body
* @param Vec 2 newVelocity - the velocity to be set to
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
* @param Vec 2 newVelocity - the velocity to be set to
* @param size_t ID - ID of object to set position
* @return void
*************************************************************************/
void Physics::SetVelocity(Vec2 velocity, size_t ID) {
	if (objectFactory->GetGameObjectByID(ID) != nullptr &&
		objectFactory->GetGameObjectByID(ID)->Has(ComponentType::PHYSICS_BODY) != -1) {
		bodyList.at(ID)->velocity = velocity;
	}
}
/**************************************************************************
* @brief Set the rotation speed of one object's Physics Body
* @param float rotSpeed - the rotation speed to be set to
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
* @param float rotSpeed - the rotation speed to be set to
* @param size_t ID - ID of object to set rotation speed
* @return void
*************************************************************************/
void Physics::SetRotationSpeed(float rotSpeed, size_t ID) {
	if (objectFactory->GetGameObjectByID(ID) != nullptr &&
		objectFactory->GetGameObjectByID(ID)->Has(ComponentType::PHYSICS_BODY) != -1) {
		bodyList.at(ID)->rotationSpeed = rotSpeed;
	}
}
void Physics::SetCurrentRotationSpeed(float rotSpeed) {
	std::map<size_t, PhysicsBody*>::iterator it = bodyList.begin();
	for (; it != bodyList.end(); it++) {
		PhysicsBody* body = it->second;
		body->currentRotationSpeed = rotSpeed;
	}
}
void Physics::SetCurrentRotationSpeed(float rotSpeed, size_t ID) {
	if (objectFactory->GetGameObjectByID(ID) != nullptr &&
		objectFactory->GetGameObjectByID(ID)->Has(ComponentType::PHYSICS_BODY) != -1) {
		bodyList.at(ID)->currentRotationSpeed = rotSpeed;
	}
}
/**************************************************************************
* @brief Set the direction of one object's Physics Body
* @param Vec2 dir - the direction to be set to
* @param size_t ID - ID of object to set direction
* @return void
*************************************************************************/
void Physics::SetDirection(Vec2 dir, size_t ID) {
	if (objectFactory->GetGameObjectByID(ID) != nullptr &&
		objectFactory->GetGameObjectByID(ID)->Has(ComponentType::PHYSICS_BODY) != -1) {
		Vector2DNormalize(bodyList.at(ID)->direction, dir);
	}
}
/**************************************************************************
* @brief Helper function to move an object backwards
* @param size_t ID - ID of object to move
* @return void
*************************************************************************/
void Physics::MoveBackwards(size_t ID) {
	if (objectFactory->GetGameObjectByID(ID) != nullptr &&
		objectFactory->GetGameObjectByID(ID)->Has(ComponentType::PHYSICS_BODY) != -1) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(-bodyList.at(ID)->direction.x, -bodyList.at(ID)->direction.y);
	}
}
/**************************************************************************
* @brief Helper function to move an object forward
* @param size_t ID - ID of object to move
* @return void
*************************************************************************/
void Physics::MoveForward(size_t ID) {
	if (objectFactory->GetGameObjectByID(ID) != nullptr &&
		objectFactory->GetGameObjectByID(ID)->Has(ComponentType::PHYSICS_BODY) != -1) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(bodyList.at(ID)->direction.x, bodyList.at(ID)->direction.y);
	}
}
/**************************************************************************
* @brief Helper function to move an object left
* @param size_t ID - ID of object to move
* @return void
*************************************************************************/
void Physics::MoveLeft(size_t ID) {
	if (objectFactory->GetGameObjectByID(ID) != nullptr &&
		objectFactory->GetGameObjectByID(ID)->Has(ComponentType::PHYSICS_BODY) != -1) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(-bodyList.at(ID)->direction.x, bodyList.at(ID)->direction.y);
	}
}
/**************************************************************************
* @brief Helper function to move an object right
* @param size_t ID - ID of object to move
* @return void
*************************************************************************/
void Physics::MoveRight(size_t ID) {
	if (objectFactory->GetGameObjectByID(ID) != nullptr &&
		objectFactory->GetGameObjectByID(ID)->Has(ComponentType::PHYSICS_BODY) != 1) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(bodyList.at(ID)->direction.x, bodyList.at(ID)->direction.y);
	}
}
/**************************************************************************
* @brief Calculate direction vector from angle of rotation
* @param float angle - angle to convert to vector (in radians)
* @return void
*************************************************************************/
Vec2 Physics::AngleToVec(float angle) {
	//angle should be in radians
	Vec2 dir = Vec2(-sinf(angle), cosf(angle));
	return dir;
}