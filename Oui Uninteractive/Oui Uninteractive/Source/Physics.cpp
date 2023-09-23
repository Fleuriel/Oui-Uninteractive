#include "Physics.h"
#include "ComponentFactory.h"
#include "ObjectFactory.h"
#include "Vector2D.h"
#include <iostream>
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
	ComponentFactory<PhysicsBody>* testPtr = new ComponentFactory<PhysicsBody>(ComponentType::PhysicsBody);
	objectFactory->AddComponentFactory(ComponentType::PhysicsBody, testPtr);
	ComponentFactory<Transform>* testPtr2 = new ComponentFactory<Transform>(ComponentType::Transform);
	objectFactory->AddComponentFactory(ComponentType::Transform, testPtr2);
}
/**************************************************************************
* @brief Update Function of the Physics System
* @param float dt - delta time
* @return void
*************************************************************************/
void Physics::Update(float dt) {

	for (PhysicsBody* body : bodyList) {
		if (body->isStatic) {
			continue;
		}
		//calculate physics
		Vector2DNormalize(body->direction, body->direction + body->AngleToVec(body->txPtr->rotation * (M_PI / 180.f)));
		
		body->txPtr->position = body->txPtr->position + body->velocity * dt;

		body->velocity = body->velocity + body->acceleration * dt;
		body->txPtr->rotation = body->txPtr->rotation + body->rotationSpeed * dt;

		//apply to object
		body->txPtr->shape->Update(body->txPtr->position.x, body->txPtr->position.y, body->txPtr->scale, body->txPtr->rotation, true);	
	}

}
/**************************************************************************
* @brief Add force to all object's Physics Body
* @param Vec 2 force - force to be added to object
* @return void
*************************************************************************/
void Physics::addForce(Vec2 force) {
	for (PhysicsBody* body : bodyList) {
		body->accumulatedForce += force;
	}
}
/**************************************************************************
* @brief Set the position of all object's Physics Body
* @param Vec 2 pos - the position to be set to
* @return void
*************************************************************************/
void Physics::setPosition(Vec2 pos) {
	for (PhysicsBody* body : bodyList) {
		body->txPtr->position = pos;
	}
}
/**************************************************************************
* @brief Set the position of one object's Physics Body
* @param Vec2 pos - the position to be set to
* @param size_t ID - ID of object to set position
* @return void
*************************************************************************/
void Physics::setPosition(Vec2 pos, size_t ID) {
	
	if (ID < bodyList.size()) {
		bodyList.at(ID)->txPtr->position = pos;	
	}
}
/**************************************************************************
* @brief Set the velocity of all object's Physics Body
* @param Vec 2 newVelocity - the velocity to be set to
* @return void
*************************************************************************/
void Physics::setVelocity(Vec2 newVelocity) {
	for (PhysicsBody* body : bodyList) {
		body->velocity = newVelocity;
	}
}
/**************************************************************************
* @brief Set the velocity of one object's Physics Body
* @param Vec 2 newVelocity - the velocity to be set to
* @param size_t ID - ID of object to set position
* @return void
*************************************************************************/
void Physics::setVelocity(Vec2 velocity, size_t ID) {
	if (ID < bodyList.size()) {
		bodyList.at(ID)->velocity = velocity;
	}
}
void Physics::setRotationSpeed(float rotSpeed) {
	for (PhysicsBody* body : bodyList) {
		body->rotationSpeed = rotSpeed;
	}
}
void Physics::setRotationSpeed(float rotSpeed, size_t ID) {
	if (ID < bodyList.size()) {
		bodyList.at(ID)->rotationSpeed = rotSpeed;
	}
}
void Physics::setDirection(Vec2 dir, size_t ID) {
	if (ID < bodyList.size()) {
		Vector2DNormalize(bodyList.at(ID)->direction, dir);
	}
}
void Physics::MoveBackwards(size_t ID) {
	if (ID < bodyList.size()) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(-bodyList.at(ID)->direction.x, -bodyList.at(ID)->direction.y);
	}
}
void Physics::MoveForward(size_t ID) {
	if (ID < bodyList.size()) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(bodyList.at(ID)->direction.x, bodyList.at(ID)->direction.y);
	}
}
void Physics::MoveLeft(size_t ID) {
	if (ID < bodyList.size()) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(-bodyList.at(ID)->direction.x, bodyList.at(ID)->direction.y);
	}
}
void Physics::MoveRight(size_t ID) {
	if (ID < bodyList.size()) {
		bodyList.at(ID)->velocity = bodyList.at(ID)->speed * Vec2(bodyList.at(ID)->direction.x, bodyList.at(ID)->direction.y);
	}
}
