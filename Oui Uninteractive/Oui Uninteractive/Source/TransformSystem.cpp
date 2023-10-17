#include "TransformSystem.h"
#include "Transform.h"
#include "ComponentFactory.h"
#include "ObjectFactory.h"

void TransformSystem::Initialize() {
	ComponentFactory<Transform>* testPtr2 = new ComponentFactory<Transform>(ComponentType::TRANSFORM);
	objectFactory->AddComponentFactory(ComponentType::TRANSFORM, testPtr2);
}
void TransformSystem::Update(float dt) {
	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	std::map<size_t, GameObject*>::iterator it = copyMap.begin();

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