#include "ColliderSystem.h"

void Collider::Initialize() {
	colliderSys->colliderMap.insert(std::pair<size_t, Collider*>(GetOwner()->GetGameObjectID(), this));
	Transform* gameObjTX = GET_COMPONENT(GetOwner(), Transform, ComponentType::TRANSFORM);
	tx->position = gameObjTX->position;
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
	newCollider->boundingbox->min = boundingbox->min;
	newCollider->boundingbox->max = boundingbox->max;
	newCollider->boundingbox->center = boundingbox->center;

	newCollider->tx->position = tx->position;
	newCollider->tx->rotation = tx->rotation;
	newCollider->tx->scale = tx->scale;

	return newCollider;
}
Collider::AABB::AABB() {
	
}
Collider::Collider() {
	boundingbox = new AABB();
	boundingbox->center = Vec2(0, 0);
	boundingbox->min = Vec2(0, 0);
	boundingbox->max = Vec2(0, 0);

	tx = new Transform();
}
Collider::~Collider() {
	delete tx;
	delete boundingbox;
	//colliderSys->colliderMap.erase(GetOwner()->GetGameObjectID());
	
}