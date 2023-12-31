/**************************************************************************
 * @file ColliderSystem.cpp
 * @author CHEAH Tristan Tze Hong - 100%
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 02-11-2023
 * @brief This file contains the definition of the Collider System.
 *		  This system is responsible for collision detection and sending the
 *		  collision response message to the Physics System.
 *************************************************************************/


#include "ColliderSystem.h"

ColliderSystem* colliderSys = nullptr;
/**************************************************************************
* @brief Constructor for Collider System
*************************************************************************/
ColliderSystem::ColliderSystem() {
	if (colliderSys != nullptr) {
		//instantiate collider sys
		return;
	}
	else {

		colliderSys = this;
	}
}
/**************************************************************************
* @brief Initialize function for ColliderSystem
* @return void
*************************************************************************/
void ColliderSystem::Initialize() {
	ComponentFactory<Collider>* testPtr = new ComponentFactory<Collider>(ComponentType::COLLIDER);
	objectFactory->AddComponentFactory(ComponentType::COLLIDER, testPtr);

	// Register physics and health system as an observer
	RegisterObserver("MSG_COLLISION", &physicsSys->observer);
	RegisterObserver("MSG_DAMAGE_TAKEN", &healthSys->observer);
}

/**************************************************************************
* @brief Update function for ColliderSystem
* @param dt - delta time
* @return void
*************************************************************************/
void ColliderSystem::Update(float dt) {
	if (sysManager->isPaused == false) {
		dt;
		bool bulletDestroyed{ false };
		TimeProfiler profiler(Editor::timeRecorder.colliderTime);
		for (int step = 0; step < sysManager->currentNumberOfSteps; step++) {
			for (std::map<size_t, Collider*>::iterator it = colliderMap.begin(); it != colliderMap.end(); it++) {
				Collider* collider = it->second;

				bool didCollide = false;
				for (std::map<size_t, Collider*>::iterator it2 = colliderMap.begin(); it2 != colliderMap.end(); it2++) {
					Collider* body2 = it2->second;
					if (body2->GetOwner()->GetGameObjectID() == collider->GetOwner()->GetGameObjectID()) {
						continue;
					}
					PhysicsBody* pBody1 = GET_COMPONENT(collider->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
					PhysicsBody* pBody2 = GET_COMPONENT(body2->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
					float contactTime = 0;
					bool collided = false;
					Vec2 normal = Vec2(0, 0);

					if (pBody1 != nullptr && pBody2 != nullptr) {

						Vec2 nextCycleVel = pBody1->velocity + (pBody1->forceManager.CalculateResultantForce() * pBody1->mass) * static_cast<float>(sysManager->fixedDeltaTime);
						Vec2 nextCycleVel2 = pBody2->velocity + (pBody2->forceManager.CalculateResultantForce() * pBody2->mass) * static_cast<float>(sysManager->fixedDeltaTime);

						Vec2 relVel = nextCycleVel - nextCycleVel2;

						collided = CollisionMovingRectRect(*(collider->boundingbox), *(body2->boundingbox), relVel, contactTime, normal, static_cast<float>(sysManager->fixedDeltaTime), nextCycleVel);
						//Collision Response
						if (collided) {
							didCollide = true;
							if (pBody1->GetOwner()->GetType() == "BulletPrefab" || pBody2->GetOwner()->GetType() == "BulletPrefab") {
								// Bullet collision with enemy
								if (pBody1->GetOwner()->GetType() == "BulletPrefab" && !bulletDestroyed) {
									objectFactory->DestroyObject(pBody1->GetOwner());
								}
								else if (pBody2->GetOwner()->GetType() == "BulletPrefab" && !bulletDestroyed) {
									objectFactory->DestroyObject(pBody2->GetOwner());
								}
								if (!bulletDestroyed) {
									DamageTakenMessage dmgMessage(pBody1->GetOwner(), pBody2->GetOwner());
									SendToObservers(&dmgMessage);
									bulletDestroyed = true;
								}
							}
							else if (pBody1->GetOwner()->GetType() == "EnemyBulletPrefab" || pBody2->GetOwner()->GetType() == "EnemyBulletPrefab") {
								// Bullet collision with player
								if (pBody1->GetOwner()->GetType() == "EnemyBulletPrefab" && !bulletDestroyed) {
									objectFactory->DestroyObject(pBody1->GetOwner());
								}
								else if (pBody2->GetOwner()->GetType() == "EnemyBulletPrefab" && !bulletDestroyed) {
									objectFactory->DestroyObject(pBody2->GetOwner());
								}
								if (!bulletDestroyed) {
									DamageTakenMessage dmgMessage(pBody1->GetOwner(), pBody2->GetOwner());
									SendToObservers(&dmgMessage);
									bulletDestroyed = true;
								}
							}
							else {
								if (!pBody2->isStatic) {
									//both objects can move
									float secondNorm = 0.f;
									float dp = Vector2DDotProduct(nextCycleVel, nextCycleVel2);
									if (dp > 0) {
										secondNorm = 1.f;
									}
									pBody1->forceManager.DeactivateForce(0);
									pBody1->forceManager.DeactivateForce(1);
									pBody2->forceManager.DeactivateForce(0);
									pBody2->forceManager.DeactivateForce(1);
									CollisionMessage collisionMessage(collider, body2, contactTime, normal, secondNorm, -normal);
									SendToObservers(&collisionMessage);

								}
								else {
									//coll response
									if (pBody2->isStatic) {
										pBody1->forceManager.DeactivateForce(0);
										pBody1->forceManager.DeactivateForce(1);
										CollisionMessage collisionMessage(collider, body2, contactTime, normal, 1.f, normal);
										SendToObservers(&collisionMessage);
									}
								}
							}

						}//Collision Response end		
					}
				}
				//reset collision data if no collision detected with anything
				if (didCollide == false) {
					collider->contactTime = 1.f;
					collider->contactNormal = Vec2(0, 0);
				}
			}
		}
	}
}