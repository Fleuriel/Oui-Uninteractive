#include "Transform.h"

Transform::Transform() {
	position = Vec2(0, 0);
	rotation = 0;
	scale = 0;
}

void Transform::Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };
	position.x = components["PositionX"].GetFloat();
	position.y = components["PositionY"].GetFloat();
	rotation = components["Rotation"].GetFloat();
}
