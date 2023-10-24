#include "ColliderSystem.h"
ColliderSystem* colliderSys = nullptr;
ColliderSystem::ColliderSystem() {
	if (colliderSys != nullptr) {
		//instantiate collider sys
		return;
	}
	else {

		colliderSys = this;
	}
}
void ColliderSystem::Initialize() {
	ComponentFactory<Collider>* testPtr = new ComponentFactory<Collider>(ComponentType::COLLIDER);
	objectFactory->AddComponentFactory(ComponentType::COLLIDER, testPtr);
}

void ColliderSystem::Update(float dt) {
	std::map<size_t, Collider*>::iterator it = colliderMap.begin();
	std::map<size_t, Collider*>::iterator it2 = colliderMap.begin();
	for (; it != colliderMap.end(); it++) {

		/*
			Vec2 absPosition = Vec2(0, 0);

			absPosition.x = body->txPtr->position.x + (windowSize.first / 2.0f);
			absPosition.y = body->txPtr->position.y + (windowSize.second / 2.0f);

			rowsBitArray[body->implicitGridPos.first].flip(body->GetOwner()->GetGameObjectID());
			colBitArray[body->implicitGridPos.second].flip(body->GetOwner()->GetGameObjectID());

			body->implicitGridPos.first = absPosition.x / cellWidth; //which row
			body->implicitGridPos.second = absPosition.y / cellHeight; //which col

			rowsBitArray[body->implicitGridPos.first].flip(body->GetOwner()->GetGameObjectID());
			colBitArray[body->implicitGridPos.second].flip(body->GetOwner()->GetGameObjectID());*/

		Collider* collider = it->second;
		collider->tx->position = GET_COMPONENT(collider->GetOwner(), Transform, ComponentType::TRANSFORM)->position;
		collider->boundingbox->center = collider->tx->position;
		collider->boundingbox->min = Vec2((-0.5f) * collider->tx->scale + collider->tx->position.x, (-0.5f) * collider->tx->scale + collider->tx->position.y);
		collider->boundingbox->max = Vec2((0.5f) * collider->tx->scale + collider->tx->position.x, (0.5f) * collider->tx->scale + collider->tx->position.y);
		for (; it2 != colliderMap.end(); it2++) {
			Collider* body2 = it2->second;
			if (body2->GetOwner()->GetGameObjectID() == collider->GetOwner()->GetGameObjectID()) {
				continue;
			}
			CollisionStaticDynamicRectRect(*(collider->boundingbox), *(body2->boundingbox));
		}

	}
	//insert collision detection here
	//response should be inside the function
}