#include "Transform.h"

Transform::Transform() {
	position = Vec2(-200,-100);
	rotation = 0;
	scale = 200.f;
}
void Transform::Initialize() {
	GetOwner()->shape->InitObjects(position.x, position.y, scale, scale);
}

void Transform::Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };
	position.x = components["PositionX"].GetFloat();
	position.y = components["PositionY"].GetFloat();
	rotation = components["Rotation"].GetFloat();
}
