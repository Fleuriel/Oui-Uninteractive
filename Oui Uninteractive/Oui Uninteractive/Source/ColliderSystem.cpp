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
	
	


	for (std::map<size_t, Collider*>::iterator it = colliderMap.begin(); it != colliderMap.end(); it++) {
		Collider* collider = it->second;
		collider->contactTime = 1.0f;

		collider->tx->position = GET_COMPONENT(collider->GetOwner(), Transform, ComponentType::TRANSFORM)->position;
		collider->boundingbox->center = collider->tx->position;
		collider->boundingbox->min = Vec2((-0.5f) * collider->tx->scale + collider->tx->position.x, (-0.5f) * collider->tx->scale + collider->tx->position.y);
		collider->boundingbox->max = Vec2((0.5f) * collider->tx->scale + collider->tx->position.x, (0.5f) * collider->tx->scale + collider->tx->position.y);

		
			for (std::map<size_t, Collider*>::iterator it2 = colliderMap.begin(); it2 != colliderMap.end(); it2++) {
				Collider* body2 = it2->second;
				if (body2->GetOwner()->GetGameObjectID() == collider->GetOwner()->GetGameObjectID()) {
					continue;
				}
				PhysicsBody* pBody1 = GET_COMPONENT(collider->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
				PhysicsBody* pBody2 = GET_COMPONENT(body2->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
				float contactTime = 0;
				bool collided = false;
				if (Vector2DLength(pBody1->velocity) > 0 && Vector2DLength(pBody2->velocity) > 0) {
					Vec2 normal = Vec2(0, 0);
					Vec2 contactPt = Vec2(0, 0);
					collided = CollisionMovingRectRect(*(collider->boundingbox), *(body2->boundingbox), pBody1->velocity, pBody2->velocity, contactTime, normal, contactPt, GetDT());
					//dynamic coll response
					if (collided) {
						//Vec2 relVelocity = pBody2->velocity - pBody1->velocity;
						//pBody1->forceManager.ApplyToForce(normal * Vec2(abs(pBody1->velocity.x), abs(pBody1->velocity.y)), (1 - contactTime), 0.25f,FORCE_INDEX::EXTERNAL);
						//pBody1->txPtr->position = contactPt;/*normal * Vec2(abs(relVelocity.x), abs(relVelocity.y)) * GetDT() * (1 - contactTime);*/
						/*w += normal * Vec2(abs(pBody1->velocity.x), abs(pBody1->velocity.y)) * (1 - contactTime);*/
						pBody1->forceManager.DeactivateForce(0);
						pBody1->forceManager.DeactivateForce(1);
						collider->contactTime = contactTime;
						std::cout << contactTime << "\n";
						std::cout << normal.x << "|" << normal.y << "\n";
					
					}
					
				}
				else {
					collided = CollisionStaticDynamicRectRect(*(collider->boundingbox), *(body2->boundingbox));
					
					if (collided) {
					std::cout << "Static Collision\n";
						Vec2 normal = Vec2(0, 0);
						float depth = CalculateEntryTimeAndNormal(collider->boundingbox, body2->boundingbox, pBody1->velocity, normal.x, normal.y);
						Vector2DNormalize(normal, normal);
						CollisionMessage collisionMessage(collider, body2, depth, normal);
						ProcessMessage(&collisionMessage);
					}
					
				}
				

				//bool staticCollided = CollisionStaticDynamicRectRect(*(collider->boundingbox), *(body2->boundingbox));
				//float dynamicCollided = 0.f;
				//PhysicsBody* pBody1 = GET_COMPONENT(collider->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
				//if (!staticCollided) {

				//	PhysicsBody* pBody2 = GET_COMPONENT(body2->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);

				//	float tFirst = 0.0f;
				//	dynamicCollided = CollisionMovingRectRect(*(collider->boundingbox), *(body2->boundingbox), pBody1->velocity, pBody2->velocity, tFirst);
				//	if (dynamicCollided) {
				//		std::cout << "!\n";
				//		pBody1->txPtr->position = pBody1->txPtr->previousPosition + (1 - tFirst) * pBody1->velocity * dt;
				//	}
				//}
				//if (staticCollided) {
				//	std::cout << "Static Collision\n";
				//	Vec2 normal = Vec2(0, 0);
				//	float depth = CalculateEntryTimeAndNormal(collider->boundingbox, body2->boundingbox, pBody1->velocity, normal.x, normal.y);
				//	Vector2DNormalize(normal, normal);
				//	//	CollisionMessage collisionMessage(collider, body2, depth, normal);
				//	//	ProcessMessage(&collisionMessage);
				//}
				//else if (staticCollided == false && dynamicCollided == false) {

				//}
			}
		
	}

	//BroadPhase();

	//Narrow Phase
 	/*for (std::set<int> colSet : collisionData) {
		for (int num : colSet) {
			std::set<int>::iterator it = colSet.upper_bound(num);
			if (it != colSet.end()) {
				CollisionStaticDynamicRectRect(*(colliderMap[num])->boundingbox, *(colliderMap[*it])->boundingbox);
			}
		}
	}*/

//	}
	//insert collision detection here
	//response should be inside the function
	}