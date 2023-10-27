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
	mass = 50.f;
	velocity = Vec2(0, 0);
	acceleration = Vec2(0, 0);
	isStatic = false;
	txPtr = nullptr;
	rotationSpeed = 0;
	currentRotationSpeed = 0;
	direction = Vec2(0, 0);
	speed = 50;
	frictionForce = 20;
}
/**************************************************************************
* @brief Destructor for PhysicsBody component
*************************************************************************/
PhysicsBody::~PhysicsBody() {
	physicsSys->bodyList.erase(GetOwner()->GetGameObjectID());
	for (LinearForce* force : forceManager.forceVec) {
		delete force;
	}
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
	physicsSys->bodyList.insert(std::pair<size_t, PhysicsBody*>(GetOwner()->GetGameObjectID(), this));

}

/**************************************************************************
* @brief Initialize this instance of the PhysicsBody component via file
* @param filePath - file path to read from
* @param itr - iterator through json object
* @return void
*************************************************************************/
void PhysicsBody::Serialize(rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{itr->value};
	velocity.x = components["VelocityX"].GetFloat();
	velocity.y = components["VelocityY"].GetFloat();
	rotationSpeed = components["RotationSpeed"].GetFloat();
	speed = components["Speed"].GetFloat();
	mass = components["Mass"].GetFloat();
	isStatic = components["IsStatic"].GetBool();
	frictionForce = components["FrictionForce"].GetFloat();
}
/**************************************************************************
* @brief Function to Clone a PhysicsBody Component
* @return PhysicsBody* - the cloned PhysicsBody
*************************************************************************/
PhysicsBody* PhysicsBody::Clone() const{
	PhysicsBody* newBody = new PhysicsBody();
	
	newBody->speed = speed;
	newBody->rotationSpeed = rotationSpeed;
	newBody->mass = mass;

	for (int i = 0; i < forceManager.forceVec.size(); i++) {
		LinearForce* newForce = new LinearForce(*forceManager.forceVec[i]);
		newBody->forceManager.forceVec.push_back(newForce);
	}

	return newBody;
}

ForceManager::ForceManager() {
	forceVec.push_back(new LinearForce(0.5, false, 50));
	forceVec.push_back(new LinearForce(0.5, false, 50));
}
void ForceManager::SetMagnitude(float new_mag, FORCE_INDEX index) {

	forceVec[index]->magnitude = new_mag;
}
void ForceManager::Update(float dt) {
	int currIndex = 0;
	for (LinearForce* force : forceVec) {
		if (force->isActive) {
			force->age += sysManager->fixedDeltaTime;
			if (force->age >= force->lifetime) {
				DeactivateForce(currIndex);
			}
		}
		currIndex++;
	}
}

void ForceManager::AddForce(LinearForce* force) {
	forceVec.push_back(force);
}
void ForceManager::DeactivateForce(int index) {
	forceVec[index]->age = 0.0f;
	forceVec[index]->isActive = false;
	forceVec[index]->direction = Vec2(0, 0);
	forceVec[index]->magnitude = 0;
}
void ForceManager::DeactivateForce(FORCE_INDEX index) {
	forceVec[index]->age = 0.0f;
	forceVec[index]->isActive = false;
	forceVec[index]->direction = Vec2(0, 0);
	forceVec[index]->magnitude = 0;
}
void ForceManager::SetActive(bool activeFlag, FORCE_INDEX index) {
	forceVec[index]->isActive = activeFlag;
}
void ForceManager::SetDirection(Vec2 dir, FORCE_INDEX index) {
	forceVec[index]->direction = dir;
}

void ForceManager::SetLifetime(float lf, FORCE_INDEX index) {
	forceVec[index]->lifetime = lf;
}
void ForceManager::ApplyToForce(Vec2 direction, float magnitude, float lifetime, FORCE_INDEX index) {
	if (index < forceVec.size()) {
		Vec2 combinedForce = (forceVec[index]->direction * forceVec[index]->magnitude) + (direction * magnitude);
		forceVec[index]->magnitude = Vector2DLength(combinedForce);
		Vector2DNormalize(forceVec[index]->direction, combinedForce);
		forceVec[index]->lifetime = lifetime;
		forceVec[index]->isActive = true;
	}
}
Vec2 ForceManager::CalculateResultantForce() {
	Vec2 summedForce = Vec2(0.0f, 0.0f);
	for (LinearForce* force : forceVec) {
		if (force->isActive) {
			summedForce += force->direction * force->magnitude;
		}
	}
	return summedForce;
}
LinearForce::LinearForce(float newLifetime, bool activeFlag, float newMagnitude) {
	lifetime = newLifetime;
	age = 0.0f;
	isActive = activeFlag;
	magnitude = newMagnitude;
}
