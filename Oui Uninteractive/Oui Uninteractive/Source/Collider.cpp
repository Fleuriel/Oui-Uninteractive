#include "ColliderSystem.h"

void Collider::Initialize() {
	colliderSys->colliderMap.insert(std::pair<size_t, Collider*>(GetOwner()->GetGameObjectID(), this));
}

void Collider::Serialize(rapidjson::Value::ConstMemberIterator& itr) {

}
Collider* Collider::Clone() const{
	Collider* newCollider = new Collider();
	newCollider->boundingbox->min = boundingbox->min;
	newCollider->boundingbox->max = boundingbox->max;
	newCollider->boundingbox->center = boundingbox->center;

	newCollider->tx = tx->Clone();

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
	tx->Initialize();
}
Collider::~Collider() {
	colliderSys->colliderMap.erase(GetOwner()->GetGameObjectID());
	delete tx;
	delete boundingbox;
}