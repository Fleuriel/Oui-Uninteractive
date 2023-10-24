#include "Collider.h"

void Collider::Initialize() {

}
void Collider::Serialize(rapidjson::Value::ConstMemberIterator& itr) {

}
Collider* Collider::Clone() const{
	Collider* newCollider = new Collider();
	newCollider->boundingbox->min = boundingbox->min;
	newCollider->boundingbox->max = boundingbox->max;
	newCollider->boundingbox->center = boundingbox->center;

	newCollider->boundingbox->tx = boundingbox->tx->Clone();

	return newCollider;
}
Collider::AABB::AABB() {
	tx = new Transform();
	tx->Initialize();
}
Collider::Collider() {
	boundingbox = new AABB();
	boundingbox->center = Vec2(0, 0);
	boundingbox->min = Vec2(0, 0);
	boundingbox->max = Vec2(0, 0);
}
Collider::~Collider() {
	delete boundingbox->tx;
	delete boundingbox;
}