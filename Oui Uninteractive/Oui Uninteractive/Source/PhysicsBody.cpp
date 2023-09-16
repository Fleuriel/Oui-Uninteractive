#include "PhysicsBody.h"
#include "Physics.h"
PhysicsBody::PhysicsBody() {
	position = Vec2(0, 0);
	velocity = Vec2(0, 0);
	acceleration = Vec2(0, 0);
	isStatic = false;
}
void PhysicsBody::Initialize() {
	//Transform
	//assign pos to transform
	//txPtr = GetOwner()->GetComponentType(ComponentType::Transform);
	//position = txPtr->position;

	physicsSys->bodyList.push_back(this);

}