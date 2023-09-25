#include "Physics.h"

/**************************************************************************
* @brief Default constructor for PhysicsBody component
*************************************************************************/
PhysicsBody::PhysicsBody() {
	//position = Vec2(0, 0);
	velocity = Vec2(0, 0);
	acceleration = Vec2(0, 0);
	isStatic = false;
	txPtr = nullptr;
	rotationSpeed = 0;
	direction = Vec2(0, 0);
	speed = 50;
	boundingbox = new AABB();

	boundingbox->min = Vec2(0,0);
	boundingbox->max = Vec2(0,0);
	boundingbox->pointer = this; //this -> Pointer to current object

}

PhysicsBody::~PhysicsBody() {
	delete boundingbox;
}

/**************************************************************************
* @brief Initialize this instance of the PhysicsBody component
* @return void
*************************************************************************/
void PhysicsBody::Initialize() {
	//Transform
	//assign pos to transform
	if (GetOwner()->Has(ComponentType::TRANSFORM) != -1) {
		txPtr = GetOwner()->GetComponentType<Transform>(ComponentType::TRANSFORM);
	}
	
	physicsSys->bodyList.push_back(this);
}

/**************************************************************************
* @brief Initialize this instance of the PhysicsBody component via file
* @param const std::string& filePath - file path to read from
* @param rapidjson::Value::ConstMemberIterator& itr - iterator through json object
* @return void
*************************************************************************/
void PhysicsBody::Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{itr->value};
	velocity.x = components["VelocityX"].GetFloat();
	velocity.y = components["VelocityY"].GetFloat();
	rotationSpeed = components["RotationSpeed"].GetFloat();
	speed = components["Speed"].GetFloat();
}
PhysicsBody* PhysicsBody::Clone() const{
	PhysicsBody* newBody = new PhysicsBody();
	
	newBody->speed = speed;
	newBody->rotationSpeed = rotationSpeed;
	newBody->boundingbox = new AABB();
	newBody->boundingbox->min = boundingbox->min;
	newBody->boundingbox->max = boundingbox->max;
	newBody->boundingbox->pointer = newBody;

	return newBody;
}
