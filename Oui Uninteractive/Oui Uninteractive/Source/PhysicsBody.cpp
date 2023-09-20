#include <iostream>
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
	if (GetOwner()->Has(ComponentType::Transform) != -1) {
		txPtr = GetOwner()->GetComponentType<Transform>(ComponentType::Transform);
		position = txPtr->position;
	}

	physicsSys->bodyList.push_back(this);

}

void PhysicsBody::Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{itr->value};
	velocity.x = components["VelocityX"].GetFloat();
	velocity.y = components["VelocityY"].GetFloat();
}