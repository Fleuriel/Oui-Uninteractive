/**************************************************************************
 * @file PhysicsBody.cpp
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-09-2023
 * @brief This file contains the definition of the PhysicsBody Class,
 *		  which is a IComponent to be contained in GameObject. It holds
 *		  all data pertaining to Physics calculations such as movement
 *		  and rotation.
 *************************************************************************/
#include "Physics.h"

/**************************************************************************
* @brief Default constructor for PhysicsBody component
*************************************************************************/
PhysicsBody::PhysicsBody() {
	velocity = Vec2(0, 0);
	acceleration = Vec2(0, 0);
	isStatic = false;
	txPtr = nullptr;
	rotationSpeed = 0;
	currentRotationSpeed = 0;
	direction = Vec2(0, 0);
	speed = 50;
	boundingbox = new AABB();
	boundingbox->min = Vec2(0,0);
	boundingbox->max = Vec2(0,0);
}
/**************************************************************************
* @brief Destructor for PhysicsBody component
*************************************************************************/
PhysicsBody::~PhysicsBody() {
	physicsSys->bodyList.erase(GetOwner()->GetGameObjectID());
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
	//physicsSys->bodyList.push_back(this);
	physicsSys->bodyList.insert(std::pair<size_t, PhysicsBody*>(GetOwner()->GetGameObjectID(), this));
}

/**************************************************************************
* @brief Initialize this instance of the PhysicsBody component via file
* @param filePath - file path to read from
* @param itr - iterator through json object
* @return void
*************************************************************************/
void PhysicsBody::Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{itr->value};
	velocity.x = components["VelocityX"].GetFloat();
	velocity.y = components["VelocityY"].GetFloat();
	rotationSpeed = components["RotationSpeed"].GetFloat();
	speed = components["Speed"].GetFloat();
}
/**************************************************************************
* @brief Function to Clone a PhysicsBody Component
* @return PhysicsBody* - the cloned PhysicsBody
*************************************************************************/
PhysicsBody* PhysicsBody::Clone() const{
	PhysicsBody* newBody = new PhysicsBody();
	
	newBody->speed = speed;
	newBody->rotationSpeed = rotationSpeed;
	newBody->boundingbox->min = boundingbox->min;
	newBody->boundingbox->max = boundingbox->max;

	return newBody;
}
