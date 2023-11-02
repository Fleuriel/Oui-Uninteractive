#include "ColliderSystem.h"
#include <bit>
ColliderSystem* colliderSys = nullptr;
ColliderSystem::ColliderSystem() {
	cellHeight = 0;
	cellWidth = 0;
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
	cellWidth = windowSize.first / WIDTH;
	cellHeight = windowSize.second / HEIGHT;

	// Register physics system as an observer
	RegisterObserver("MSG_COLLISION", &physicsSys->observer);
}
void ColliderSystem::BroadPhase() {
	std::map<size_t, Collider*>::iterator it = colliderMap.begin();
	std::map<size_t, Collider*>::iterator it2 = colliderMap.begin();
	collisionData.clear();
	
	bitArray result;
	
	for (int i = 0; i < WIDTH; i++) {
		if (rowsBitArray[i].count() == 0) {
			continue;
		}
		for (int j = 0; j < HEIGHT; j++) {
			if (colBitArray[i].count() == 0) {
				continue;
			}
			result = rowsBitArray[i] & colBitArray[j];
			if (result.count() > 1) {
				int nextSetBit = 0;
				std::set<int> collisionResult;
				while (result.count() != 0) {
					int count = 0;
					for (; nextSetBit < MAX_COLLIDABLE_ENTITIES; nextSetBit++) {
						if (result.test(nextSetBit) == 1) {
							count = nextSetBit;
							result.reset(count);
							collisionResult.insert(count);
						}
					}
								
				}
				collisionData.push_back(collisionResult);
				
			}
			else {
				continue;
			}
			
		}
	}
}


void ColliderSystem::Update(float dt) {
	TimeProfiler profiler(Editor::timeRecorder.colliderTime);
	for (int step = 0; step < sysManager->currentNumberOfSteps; step++) {
		for (std::map<size_t, Collider*>::iterator it = colliderMap.begin(); it != colliderMap.end(); it++) {
			Collider* collider = it->second;
			


			collider->tx->position = GET_COMPONENT(collider->GetOwner(), Transform, ComponentType::TRANSFORM)->position;
			collider->boundingbox->center = collider->tx->position;
			collider->boundingbox->min = Vec2((-0.5f) * collider->tx->scale + collider->tx->position.x, (-0.5f) * collider->tx->scale + collider->tx->position.y);
			collider->boundingbox->max = Vec2((0.5f) * collider->tx->scale + collider->tx->position.x, (0.5f) * collider->tx->scale + collider->tx->position.y);

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
				float depth = 0.f;
				Vec2 nextCycleVel = pBody1->velocity + pBody1->forceManager.CalculateResultantForce() * pBody1->mass * static_cast<float>(sysManager->fixedDeltaTime);
				Vec2 nextCycleVel2 = pBody2->velocity + pBody2->forceManager.CalculateResultantForce() * pBody2->mass * static_cast<float>(sysManager->fixedDeltaTime);

				Vec2 relVel = nextCycleVel - nextCycleVel2;
				
				collided = CollisionMovingRectRect(*(collider->boundingbox), *(body2->boundingbox), relVel, contactTime, normal, static_cast<float>(sysManager->fixedDeltaTime), depth, nextCycleVel);
				if (collided) {
					didCollide = true;
					if (pBody1->GetOwner()->GetGameObjectID() == 0) {
						std::cout << contactTime;
					}
					if (!pBody2->isStatic) {
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
						ProcessMessage(&collisionMessage); 

					}
					else {
						//coll response
						if (pBody2->isStatic) {
							pBody1->forceManager.DeactivateForce(0);
							pBody1->forceManager.DeactivateForce(1);
							CollisionMessage collisionMessage(collider, body2, contactTime, normal, 1.f, normal);
							ProcessMessage(&collisionMessage);
						}
						
					}
				}

			}
			if (didCollide == false) {
				collider->contactTime = 1.f;
				collider->contactNormal = Vec2(0,0);
			}
		}
	}
	
	}