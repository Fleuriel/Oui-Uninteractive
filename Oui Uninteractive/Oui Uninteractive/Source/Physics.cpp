#include "Physics.h"
Physics* physicsSys = nullptr;
Physics::Physics() {
	if (physicsSys != nullptr) {
		//instantiate physics system
	}
	else {
		physicsSys = this;
	}
	
}
void Physics::Initialize() {

}
void Physics::Update(float dt) {
	//might need to store pointers to body component , KIV
	for (PhysicsBody* body : bodyList) {
		if (body->isStatic) {
			continue;
		}
		body->position = body->position + body->velocity * dt;
		body->velocity = body->velocity + body->acceleration * dt;
	}

}