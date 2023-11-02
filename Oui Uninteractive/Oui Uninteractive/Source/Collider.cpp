/**************************************************************************
 * @file Collider.cpp
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 02-11-2023
 * @brief This file contains the definition of the Collider Class,
 *		  which is a IComponent to be contained in GameObject. It holds all
 *		  data pertaining to collision detection/response
 *************************************************************************/
#include "ColliderSystem.h"
/**************************************************************************
* @brief Initialize function for Collider Component
* @return void
*************************************************************************/
void Collider::Initialize() {
	colliderSys->colliderMap.insert(std::pair<size_t, Collider*>(GetOwner()->GetGameObjectID(), this));
	Transform* gameObjTX = GET_COMPONENT(GetOwner(), Transform, ComponentType::TRANSFORM);
	if (gameObjTX != nullptr) {
		tx->position = gameObjTX->position;
	}
}
/**************************************************************************
* @brief Serialize function for Collider component
* @param itr - iterator through json object
* @return void
*************************************************************************/
void Collider::Serialize(rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };
	tx->scale = components["ColliderSize"].GetFloat();
	tx->rotation = components["ColliderRotation"].GetFloat();
}
/**************************************************************************
* @brief Function to Clone a Collider Component
* @return Collider* - the cloned Collider
*************************************************************************/
Collider* Collider::Clone() const{
	Collider* newCollider = new Collider();
	newCollider->contactTime = contactTime;
	newCollider->contactNormal = contactNormal;
	newCollider->boundingbox->min = boundingbox->min;
	newCollider->boundingbox->max = boundingbox->max;
	newCollider->boundingbox->center = boundingbox->center;

	newCollider->tx->position = tx->position;
	newCollider->tx->rotation = tx->rotation;
	newCollider->tx->scale = tx->scale;
	newCollider->boundingbox->txPtr = newCollider->tx;

	return newCollider;
}
/**************************************************************************
* @brief Constructor for AABB struct within Collider
*************************************************************************/
Collider::AABB::AABB() {
	txPtr = nullptr;
}
/**************************************************************************
* @brief Constructor for Collider
*************************************************************************/
Collider::Collider() {
	boundingbox = new AABB();
	boundingbox->center = Vec2(0, 0);
	boundingbox->min = Vec2(0, 0);
	boundingbox->max = Vec2(0, 0);
	contactTime = 0;
	contactNormal = Vec2(0, 0);
	wasColliding = false;
	tx = new Transform();

	boundingbox->txPtr = tx;
}
/**************************************************************************
* @brief Destructor for Collider
*************************************************************************/
Collider::~Collider() {
	delete tx;
	delete boundingbox;
	if (GetOwner() != nullptr) {
		colliderSys->colliderMap.erase(GetOwner()->GetGameObjectID());
	}
}