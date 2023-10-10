#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"
class TestScript : public IScript {
public:
	void Initialize() {
		logicSystem->AddLogicScript(this);
	};

	void Update(size_t gameObjectID) {
		GameObject* gObj = objectFactory->GetGameObjectByID(gameObjectID);
		Transform* tx = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM);
		PhysicsBody* physBod = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
		if (tx != nullptr && physBod != nullptr) {
			
			if (physBod->forceManager.forceVec.size() >= 1) {
				physBod->forceManager.SetActive(true, 0);
				if (tx->position.x < -300) {
					physBod->forceManager.SetDirection(Vec2(1.f, 0), 0);
				}
				else if (tx->position.x > 300) {
					physBod->forceManager.SetDirection(Vec2(-1.f, 0), 0);
				}	
			}
			
		}
	};

	void End() {};
};