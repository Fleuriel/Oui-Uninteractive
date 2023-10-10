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
			if (keyStates[GLFW_KEY_S]) {
				PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);
				playerBody->forceManager.SetActive(true, 0);
				playerBody->forceManager.SetDirection(-playerBody->direction, 0);
				//physicsSys->MoveBackwards(0);
			}

			else if (keyStates[GLFW_KEY_W]) {
				PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);
				playerBody->forceManager.SetActive(true, 0);
				playerBody->forceManager.SetDirection(playerBody->direction, 0);
				//physicsSys->MoveForward(0);
			}
			else {
				PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);
				playerBody->forceManager.DeactivateForce(0);
			}
		}
	};

	void End() {};

};