#include "ColliderSystem.h"

void Collider::Initialize() {
	colliderSys->colliderMap.insert(std::pair<size_t, Collider*>(GetOwner()->GetGameObjectID(), this));
	Transform* gameObjTX = GET_COMPONENT(GetOwner(), Transform, ComponentType::TRANSFORM);
	if (gameObjTX != nullptr) {
		tx->position = gameObjTX->position;
		boundingbox->center = tx->position;
		boundingbox->min = Vec2((-0.5f) * tx->scale + tx->position.x, (-0.5f) * tx->scale + tx->position.y);
		boundingbox->max = Vec2((0.5f) * tx->scale + tx->position.x, (0.5f) * tx->scale + tx->position.y);
	}
	else {

#ifndef _DEBUG
		std::cout << "Game object has no transform.\n";
#endif

	}
	/*
	
	if (gameObjTX != nullptr) {
		tx = gameObjTX->Clone();
	}
	else {
		std::cout << "game object has no transform\n";
	}*/
	
}

void Collider::Serialize(rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };
	tx->scale = components["ColliderSize"].GetFloat();
	tx->rotation = components["ColliderRotation"].GetFloat();
}
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
Collider::AABB::AABB() {
	txPtr = nullptr;
}
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
Collider::~Collider() {
	delete tx;
	delete boundingbox;
	if (GetOwner() != nullptr) {
		colliderSys->colliderMap.erase(GetOwner()->GetGameObjectID());
	}
}