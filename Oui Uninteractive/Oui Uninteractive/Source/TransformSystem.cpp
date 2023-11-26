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
#define PI 3.141592653589793


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
	if (sysManager->isPaused == false) {
		TimeProfiler profiler(Editor::timeRecorder.transformTime);
		std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
		std::map<size_t, GameObject*>::iterator it = copyMap.begin();

		std::map<size_t, Collider*> copyColliderMap = colliderSys->colliderMap;
		std::map<size_t, Collider*>::iterator it2 = copyColliderMap.begin();

		for (; it2 != copyColliderMap.end(); it2++) {
			Collider* collider = it2->second;
			//Update bounding box position
			if (GET_COMPONENT(collider->GetOwner(), Transform, ComponentType::TRANSFORM) != nullptr) {
				collider->tx->position = GET_COMPONENT(collider->GetOwner(), Transform, ComponentType::TRANSFORM)->position;
			}

			//collider->tx->scale = (100, 100);

			/*collider->boundingbox->center.x = collider->tx->position.x - Editor::gameWindowSize.first;
			collider->boundingbox->center.y = collider->tx->position.y - Editor::gameWindowSize.second;*/
			collider->boundingbox->center = collider->tx->position;
			collider->boundingbox->min = Vec2((-0.5f) * collider->tx->scale.x + collider->tx->position.x, (-0.5f) * collider->tx->scale.y + collider->tx->position.y);
			collider->boundingbox->max = Vec2((0.5f) * collider->tx->scale.x + collider->tx->position.x, (0.5f) * collider->tx->scale.y + collider->tx->position.y);
			collider->contactTime = 1.0f;
			if (OpenGLObject::renderBoundingBox) {
				Transform* tx = it2->second->tx;
				if (tx != nullptr) {
					Matrix3x3 scale = Matrix3x3(tx->scale.x, 0.f, 0.f,
						0.f, tx->scale.y, 0.f,
						0.f, 0.0f, 1.0f);
					float radRot = tx->rotation * (static_cast<float>(PI) / 180.0f);
					Matrix3x3 rotate = Matrix3x3(cosf(radRot), sinf(radRot), 0,
						-sinf(radRot), cosf(radRot), 0.f,
						0.f, 0.f, 1.0f);
					Matrix3x3 translate = Matrix3x3(1.f, 0.f, 0.f,
						0.f, 1.f, 0.f,
						tx->position.x, tx->position.y, 1.0f);
					tx->shape->Update(scale, rotate, translate);
					//tx->shape->Update(tx->position.x, tx->position.y, tx->scale, tx->scale, tx->rotation, false);
				}
				else {
					continue;
				}
			}
		}
		for (; it != copyMap.end(); it++) {
			Transform* tx = GET_COMPONENT(it->second, Transform, ComponentType::TRANSFORM);
			if (tx != nullptr) {
				Matrix3x3 scale = Matrix3x3(tx->scale.x, 0.f, 0.f,
					0.f, tx->scale.y, 0.f,
					0.f, 0.0f, 1.0f);
				float radRot = tx->rotation * (static_cast<float>(PI) / 180.0f);
				Matrix3x3 rotate = Matrix3x3(cosf(radRot), sinf(radRot), 0,
					-sinf(radRot), cosf(radRot), 0.f,
					0.f, 0.f, 1.0f);
				Matrix3x3 translate = Matrix3x3(1.f, 0.f, 0.f,
					0.f, 1.f, 0.f,
					tx->position.x, tx->position.y, 1.0f);
				tx->shape->Update(scale, rotate, translate);
				//tx->shape->Update(tx->position.x, tx->position.y, tx->scale, tx->scale, tx->rotation, false);
			}
			else {
				continue;
			}
		}
	}
}
