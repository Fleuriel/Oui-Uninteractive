#include "Physics.h"
#include "ComponentFactory.h"
#include "ObjectFactory.h"
#include <iostream>
Physics* physicsSys = nullptr;
Physics::Physics() {
	if (physicsSys == nullptr) {
		//instantiate physics system
		return;
	}
	else {
		physicsSys = this;
	}
	
}
void Physics::Initialize() {
	//Register Component creator of Body here
	objectFactory->AddComponentFactory("PhysicsBody", new ComponentFactory<PhysicsBody>(ComponentType::PhysicsBody));
	std::cout << "I WILL ADD THE PHYSICS BODY FACTORY HERE";
}
void Physics::Update(float dt) {

	for (PhysicsBody* body : bodyList) {
		if (body->isStatic) {
			continue;
		}
		body->position = body->position + body->velocity * dt;
		body->velocity = body->velocity + body->acceleration * dt;
		body->txPtr->position = body->position;
	}

}
void Physics::addForce(Vec2 force) {
	for (PhysicsBody* body : bodyList) {
		body->accumulatedForce += force;
	}
}
void Physics::setPosition(Vec2 pos) {
	for (PhysicsBody* body : bodyList) {
		body->position = pos;
	}
}