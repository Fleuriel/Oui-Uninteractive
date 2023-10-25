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

		Vec2 absPosition = Vec2(0, 0);

		absPosition.x = collider->boundingbox->min.x + (windowSize.first / 2.0f);
		absPosition.y = collider->boundingbox->min.y + (windowSize.second / 2.0f);
		int newRowIndex = absPosition.x / cellWidth;
		int newColIndex = absPosition.y / cellHeight;

		if (newRowIndex != collider->implicitGridPos.first) {
			if (newRowIndex < WIDTH) {
				rowsBitArray[collider->implicitGridPos.first].reset(collider->GetOwner()->GetGameObjectID());
				collider->implicitGridPos.first = newRowIndex; //which row
				rowsBitArray[collider->implicitGridPos.first].set(collider->GetOwner()->GetGameObjectID());
			}
			else {
				std::cout << "SHIT\n";
			}
		}
		if (newColIndex != collider->implicitGridPos.second) {
			if (newColIndex < HEIGHT) {
				colBitArray[collider->implicitGridPos.second].reset(collider->GetOwner()->GetGameObjectID());
				collider->implicitGridPos.second = newColIndex; //which col
				colBitArray[collider->implicitGridPos.second].set(collider->GetOwner()->GetGameObjectID());
			}
			else {
				std::cout << "SHIT\n";
			}
		}

		/*Vec2 absPosition2 = Vec2(0, 0);

		absPosition2.x = collider->boundingbox->max.x + (windowSize.first / 2.0f);
		absPosition2.y = collider->boundingbox->max.x + (windowSize.second / 2.0f);
		int newRowIndex2 = absPosition.x / cellWidth;
		int newColIndex2 = absPosition.y / cellHeight;

		if (newRowIndex2 != collider->implicitGridPos2.first) {
			if (newRowIndex2 < WIDTH) {
				rowsBitArray[collider->implicitGridPos2.first].reset(collider->GetOwner()->GetGameObjectID());
				collider->implicitGridPos2.first = newRowIndex2; //which row
				rowsBitArray[collider->implicitGridPos2.first].set(collider->GetOwner()->GetGameObjectID());
			}
		}
		if (newColIndex2 != collider->implicitGridPos2.second) {
			if (newColIndex < HEIGHT) {
				colBitArray[collider->implicitGridPos2.second].reset(collider->GetOwner()->GetGameObjectID());
				collider->implicitGridPos2.second = newColIndex2; //which col
				colBitArray[collider->implicitGridPos2.second].set(collider->GetOwner()->GetGameObjectID());
			}
		}*/
		
		/*for (; it2 != colliderMap.end(); it2++) {
			Collider* body2 = it2->second;
			if (body2->GetOwner()->GetGameObjectID() == collider->GetOwner()->GetGameObjectID()) {
				continue;
			}
			CollisionStaticDynamicRectRect(*(collider->boundingbox), *(body2->boundingbox));
		}*/
	}

	BroadPhase();

	//Narrow Phase
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