/**************************************************************************
 * @file TransformSystem.cpp
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 02-11-2023
 * @brief This file contains the definition of the Transform System.
 *		  This system is responsible updating the positions of the transforms
 *************************************************************************/

#include "TransformSystem.h"


/**************************************************************************
* @brief Initialize function for Transform System
* @return void
*************************************************************************/
void TransformSystem::Initialize() {
	ComponentFactory<Transform>* testPtr2 = new ComponentFactory<Transform>(ComponentType::TRANSFORM);
	objectFactory->AddComponentFactory(ComponentType::TRANSFORM, testPtr2);
}
/**************************************************************************
* @brief Update function for Transform System
* @param dt - delta time
* @return void
*************************************************************************/
void TransformSystem::Update(float) {
	TimeProfiler profiler(Editor::timeRecorder.transformTime);
	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	std::map<size_t, GameObject*>::iterator it = copyMap.begin();
	
	std::map<size_t, Collider*> copyColliderMap = colliderSys->colliderMap;
	std::map<size_t, Collider*>::iterator it2 = copyColliderMap.begin();
	
	for (; it2 != copyColliderMap.end(); it2++) {
		Collider* collider = it2->second;
		//Update bounding box position
		collider->tx->position = GET_COMPONENT(collider->GetOwner(), Transform, ComponentType::TRANSFORM)->position;
		collider->boundingbox->center = collider->tx->position;
		collider->boundingbox->min = Vec2((-0.5f) * collider->tx->scale + collider->tx->position.x, (-0.5f) * collider->tx->scale + collider->tx->position.y);
		collider->boundingbox->max = Vec2((0.5f) * collider->tx->scale + collider->tx->position.x, (0.5f) * collider->tx->scale + collider->tx->position.y);
		collider->contactTime = 1.0f;
		if (OpenGLObject::renderBoundingBox) {
			Transform* tx = it2->second->tx;
			if (tx != nullptr) {
				tx->shape->Update(tx->position.x, tx->position.y, tx->scale, tx->scale, tx->rotation, true);
			}
			else {
				continue;
			}
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
