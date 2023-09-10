#include "Physics.h"
Physics::Physics() {
	if (physicSys != nullptr) {
		
	}
	else {
		physicSys = this;
	}
	
}
void Physics::Initialize() {

}
void Physics::Update(float dt) {
	//might need to store pointers to body component , KIV
	for (PhysicsBody body : bodyList) {
		if (body.isStatic) {
			continue;
		}
		body.position = body.position + body.velocity * dt;
		body.velocity = body.velocity + body.acceleration * dt;
	}

}