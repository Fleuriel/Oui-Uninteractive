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
	std::map<size_t, Collider*>::iterator it = colliderMap.begin();
	std::map<size_t, Collider*>::iterator it2 = colliderMap.begin();


	for (; it != colliderMap.end(); it++) {
		Collider* collider = it->second;

		collider->tx->position = GET_COMPONENT(collider->GetOwner(), Transform, ComponentType::TRANSFORM)->position;
		collider->boundingbox->center = collider->tx->position;
		collider->boundingbox->min = Vec2((-0.5f) * collider->tx->scale + collider->tx->position.x, (-0.5f) * collider->tx->scale + collider->tx->position.y);
		collider->boundingbox->max = Vec2((0.5f) * collider->tx->scale + collider->tx->position.x, (0.5f) * collider->tx->scale + collider->tx->position.y);

		/*Vec2 absPosition = Vec2(0, 0);

		absPosition.x = collider->tx->position.x + (windowSize.first / 2.0f);
		absPosition.y = collider->tx->position.y + (windowSize.second / 2.0f);

		int newRowIndex = absPosition.x / cellWidth; //which row
		int newColIndex = absPosition.y / cellHeight; //which col

		rowsBitArray[collider->implicitGridPos.first].reset(collider->GetOwner()->GetGameObjectID());
		colBitArray[collider->implicitGridPos.second].reset(collider->GetOwner()->GetGameObjectID());
		if (newRowIndex < 4 && newColIndex < 4) {
			collider->implicitGridPos.first = newRowIndex;
			collider->implicitGridPos.second = newColIndex;

			rowsBitArray[collider->implicitGridPos.first].set(collider->GetOwner()->GetGameObjectID());
			colBitArray[collider->implicitGridPos.second].set(collider->GetOwner()->GetGameObjectID());
		}*/
		
		for (; it2 != colliderMap.end(); it2++) {
			Collider* body2 = it2->second;
			if (body2->GetOwner()->GetGameObjectID() == collider->GetOwner()->GetGameObjectID()) {
				continue;
			}

			PhysicsBody* pBody1 = GET_COMPONENT(collider->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
			bool staticCollided = CollisionStaticDynamicRectRect(*(collider->boundingbox), *(body2->boundingbox));
			bool dynamicCollided;
			if (!staticCollided) {
				PhysicsBody* pBody2 = GET_COMPONENT(body2->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);
				dynamicCollided = CollisionMovingRectRect(*(collider->boundingbox), *(body2->boundingbox), pBody1->velocity, pBody2->velocity);
				if (dynamicCollided) {

				}
			}
			
			if (staticCollided){
				Vec2 normal = Vec2(0,0);
				float depth = CalculateEntryTimeAndNormal(collider->boundingbox, body2->boundingbox, pBody1->velocity, normal.x, normal.y);
				//depth = depth / Vector2DLength(normal);
				float halfDepth = depth / 2;
				Vec2 dir = body2->boundingbox->center - collider->boundingbox->center;
				Vector2DNormalize(normal, normal);
				if (Vector2DDotProduct(dir, normal) < 0.f) {
					normal = -normal;
				}

				
				//coll response
				Vec2 penetration = normal * halfDepth;
				Transform* tx1 = GET_COMPONENT(objectFactory->GetGameObjectByID(0), Transform, ComponentType::TRANSFORM);
				Transform* tx2 = GET_COMPONENT(body2->GetOwner(), Transform, ComponentType::TRANSFORM);
				PhysicsBody* pBody2 = GET_COMPONENT(body2->GetOwner(), PhysicsBody, ComponentType::PHYSICS_BODY);

				if (pBody2->isStatic) {
					tx1->position += normal * depth;
				}
				else {
				//	pBody1->forceManager.ApplyToForce(normal, depth / 2, 0.1f, FORCE_INDEX::EXTERNAL);
					tx1->position += normal * (depth / 2);
				//	pBody2->forceManager.ApplyToForce(-normal, depth / 2, 0.1f, FORCE_INDEX::EXTERNAL);
					tx2->position += (-normal * (depth / 2));
				}

			/*	Vec2 direction;
				Vector2DNormalize(direction, pBody1->velocity);
				float magnitude = Vector2DLength(pBody1->velocity);
				pBody1->forceManager.ApplyToForce(-direction, pBody1->speed, 0.2f, FORCE_INDEX::EXTERNAL);*/
			//	pBody1->forceManager.DeactivateForce(FORCE_INDEX::INTERNAL);
			}
			else if (staticCollided == false && dynamicCollided == false) {
				
			}
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