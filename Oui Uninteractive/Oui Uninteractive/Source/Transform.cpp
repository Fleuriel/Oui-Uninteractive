#include "Transform.h"

Transform::Transform() {
	position = Vec2(-250,50);
	rotation = 0;
	scale = 100.f;
	shape = new OpenGLObject();
}
Transform::~Transform() {
	delete shape;
}
void Transform::Initialize() {
	shape->InitObjects(position.x, position.y, scale, scale, 0, 0);
}

void Transform::Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };
	position.x = components["PositionX"].GetFloat();
	position.y = components["PositionY"].GetFloat();
	rotation = components["Rotation"].GetFloat();
}
