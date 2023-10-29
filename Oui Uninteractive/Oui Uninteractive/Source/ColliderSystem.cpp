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
		collider->contactNormal = Vec2(1, 1);

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
				//collided = CollisionStaticDynamicRectRect(*(collider->boundingbox), *(body2->boundingbox));
				Vec2 normal = Vec2(0, 0);
				Vec2 cnPt = Vec2(0, 0);
				float ctTime = 0.f;
				float depth = 0.f;
				collided = CollisionMovingRectRect(*(collider->boundingbox), *(body2->boundingbox), pBody1->velocity, pBody2->velocity, contactTime, normal, cnPt, GetDT(), depth);
				if (collided) {
					if (!pBody2->isStatic) {

						
						//float depth = CalculateEntryTimeAndNormal(collider->boundingbox, body2->boundingbox, pBody1->velocity, normal.x, normal.y);
					//	MovingPointRectCollision(collider->boundingbox->center, pBody1->velocity * GetDT(), *(body2->boundingbox), cnPt, normal, ctTime, depth);
						Vector2DNormalize(normal, normal);
						CollisionMessage collisionMessage(collider, body2, depth, normal);
						ProcessMessage(&collisionMessage);

					}
					else {
						float depth = CalculateEntryTimeAndNormal(collider->boundingbox, body2->boundingbox, pBody1->velocity, normal.x, normal.y);
						float halfDepth = depth / 2;
						Vec2 dir = body2->boundingbox->center - collider->boundingbox->center;
						if (Vector2DDotProduct(dir, normal) < 0.f) {
								normal = -normal;
							
						}

						//coll response

						//	PhysicsBody* pBody2 = GET_COMPONENT(body2->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
						PhysicsBody* pBody1 = physicsSys->bodyList[collider->GetOwner()->GetGameObjectID()];
						PhysicsBody* pBody2 = physicsSys->bodyList[body2->GetOwner()->GetGameObjectID()];

						if (pBody2->isStatic) {
							pBody1->txPtr->position += normal * depth;
							pBody1->velocity += normal * depth;// * msg->GetFirstCollider()->contactTime;
						}
						else if (pBody1->isStatic) {
							pBody2->txPtr->position += (-normal) * depth;
							pBody2->velocity += normal * depth;//* msg->GetFirstCollider()->contactTime;
						}
					}
				}
				
				

				
			}
		
	}

	
	}