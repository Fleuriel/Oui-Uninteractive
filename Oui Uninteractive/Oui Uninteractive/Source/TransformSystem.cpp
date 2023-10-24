#include "TransformSystem.h"



void TransformSystem::Initialize() {
	ComponentFactory<Transform>* testPtr2 = new ComponentFactory<Transform>(ComponentType::TRANSFORM);
	objectFactory->AddComponentFactory(ComponentType::TRANSFORM, testPtr2);
}
void TransformSystem::Update(float dt) {
	TimeProfiler profiler(Editor::timeRecorder.transformTime);
	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	std::map<size_t, GameObject*>::iterator it = copyMap.begin();
	
	std::map<size_t, Collider*> copyMap2 = colliderSys->colliderMap;
	std::map<size_t, Collider*>::iterator it2 = copyMap2.begin();
	for (; it2 != copyMap2.end(); it2++) {
		Transform* tx = it2->second->tx;
		if (tx != nullptr) {
			tx->shape->Update(tx->position.x, tx->position.y, tx->scale, tx->scale, tx->rotation, true);
		}
		else {
			continue;
		}
	}
	for (; it != copyMap.end(); it++) {
		Transform* tx = GET_COMPONENT(it->second, Transform, ComponentType::TRANSFORM);
		if (tx != nullptr) {
			tx->shape->Update(tx->position.x, tx->position.y, tx->scale, tx->scale, tx->rotation, true);
		}
		else {
			continue;
		}
	}
}
TransformSystem::~TransformSystem() {

}