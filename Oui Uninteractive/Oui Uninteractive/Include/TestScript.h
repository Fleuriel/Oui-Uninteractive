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
				
				if (tx->position.x < -300) {
					physBod->forceManager.SetActive(true, FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetDirection(Vec2(1.f, 0), FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetMagnitude(physBod->speed, FORCE_INDEX::EXTERNAL);
				}
				else if (tx->position.x > 300) {
					physBod->forceManager.SetActive(true, FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetDirection(Vec2(-1.f, 0), FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetMagnitude(physBod->speed, FORCE_INDEX::EXTERNAL);
				}	
				else {
					if (physBod->forceManager.forceVec[FORCE_INDEX::EXTERNAL]->isActive == false) {
						physBod->forceManager.SetActive(true, FORCE_INDEX::EXTERNAL);
						physBod->forceManager.SetDirection(Vec2(-1.f, 0), FORCE_INDEX::EXTERNAL);
						physBod->forceManager.SetMagnitude(physBod->speed, FORCE_INDEX::EXTERNAL);
					}
				}
			}
			
		}
	};

	void End() {};
};
class TestScript2 : public IScript {
public:
	void Initialize() {
		logicSystem->AddLogicScript(this);
	};

	void Update(size_t gameObjectID) {
		GameObject* gObj = objectFactory->GetGameObjectByID(gameObjectID);
		Transform* tx = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM);
		PhysicsBody* physBod = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
		if (tx != nullptr && physBod != nullptr) {
			if (keyStates[GLFW_KEY_Z]) {
				PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
				playerBody->forceManager.ApplyToForce(Vec2(0.0f, 0.1f), 20.f, 0.3f, FORCE_INDEX::EXTERNAL);
			}
			if (keyStates[GLFW_KEY_S]) {
				PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
				playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetDirection(-playerBody->direction, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
			}
			
			else if (keyStates[GLFW_KEY_W]) {
				PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
				playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetDirection(playerBody->direction, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
			}
			else {
				PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
				playerBody->forceManager.DeactivateForce(FORCE_INDEX::INTERNAL);
			}
		}
	};

	void End() {};

};