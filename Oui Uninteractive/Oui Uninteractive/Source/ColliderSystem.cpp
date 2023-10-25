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
	for (; it != colliderMap.end(); it++) {
		Collider* collider = it->second;
		Vec2 absPosition = Vec2(0, 0);

		absPosition.x = collider->tx->position.x + (windowSize.first / 2.0f);
		absPosition.y = collider->tx->position.y + (windowSize.second / 2.0f);

		rowsBitArray[collider->implicitGridPos.first].reset(collider->GetOwner()->GetGameObjectID());
		colBitArray[collider->implicitGridPos.second].reset(collider->GetOwner()->GetGameObjectID());

		collider->implicitGridPos.first = absPosition.x / cellWidth; //which row
		collider->implicitGridPos.second = absPosition.y / cellHeight; //which col

		rowsBitArray[collider->implicitGridPos.first].set(collider->GetOwner()->GetGameObjectID());
		colBitArray[collider->implicitGridPos.second].set(collider->GetOwner()->GetGameObjectID());
	}
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
					for (; nextSetBit < 3000; nextSetBit++) {
						if (result.test(nextSetBit) == 1) {
							count = nextSetBit;
							break;
						}
					}
					result.reset(count);
					collisionResult.insert(count);			
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
	BroadPhase();

	for (; it != colliderMap.end(); it++) {
		Collider* collider = it->second;
		collider->tx->position = GET_COMPONENT(collider->GetOwner(), Transform, ComponentType::TRANSFORM)->position;
		collider->boundingbox->center = collider->tx->position;
		collider->boundingbox->min = Vec2((-0.5f) * collider->tx->scale + collider->tx->position.x, (-0.5f) * collider->tx->scale + collider->tx->position.y);
		collider->boundingbox->max = Vec2((0.5f) * collider->tx->scale + collider->tx->position.x, (0.5f) * collider->tx->scale + collider->tx->position.y);
		/*for (; it2 != colliderMap.end(); it2++) {
			Collider* body2 = it2->second;
			if (body2->GetOwner()->GetGameObjectID() == collider->GetOwner()->GetGameObjectID()) {
				continue;
			}
			CollisionStaticDynamicRectRect(*(collider->boundingbox), *(body2->boundingbox));
		}*/
	}
 	for (std::set<int> colSet : collisionData) {
		for (int num : colSet) {
			std::set<int>::iterator it = colSet.upper_bound(num);
			if (it != colSet.end()) {
				CollisionStaticDynamicRectRect(*(colliderMap[num])->boundingbox, *(colliderMap[*it])->boundingbox);
			}
		}
	}

//	}
	//insert collision detection here
	//response should be inside the function
}