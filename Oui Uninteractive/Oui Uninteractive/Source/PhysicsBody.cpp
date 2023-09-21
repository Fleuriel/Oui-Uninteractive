#include <iostream>
#include "Physics.h"
/**************************************************************************
* @brief Default constructor for PhysicsBody component
*************************************************************************/
PhysicsBody::PhysicsBody() {
	position = Vec2(0, 0);
	velocity = Vec2(0, 0);
	acceleration = Vec2(0, 0);
	isStatic = false;
}
/**************************************************************************
* @brief Initialize this instance of the PhysicsBody component
* @return void
*************************************************************************/
void PhysicsBody::Initialize() {
	//Transform
	//assign pos to transform
	if (GetOwner()->Has(ComponentType::Transform) != -1) {
		txPtr = GetOwner()->GetComponentType<Transform>(ComponentType::Transform);
		position = txPtr->position;
	}

	physicsSys->bodyList.push_back(this);

}
/**************************************************************************
* @brief Initialize this instance of the PhysicsBody component
* @param const std::string& filePath - file path to read from
* @param rapidjson::Value::ConstMemberIterator& itr - iterator through json object
* @return void
*************************************************************************/
void PhysicsBody::Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{itr->value};
	velocity.x = components["VelocityX"].GetFloat();
	velocity.y = components["VelocityY"].GetFloat();
}