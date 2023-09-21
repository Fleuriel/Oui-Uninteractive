#include "Physics.h"
#include "ComponentFactory.h"
#include "ObjectFactory.h"
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
		body->position = body->position + body->velocity * dt;
		body->velocity = body->velocity + body->acceleration * dt;
		body->txPtr->position = body->position;

		//std::cout << "X: " << body->position.x << "Y: " << body->position.y << "\n";
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
		body->position = pos;
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
		bodyList.at(ID)->position = pos;	
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