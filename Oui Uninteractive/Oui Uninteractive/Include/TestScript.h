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
			if (tx != nullptr && physBod != nullptr) {
				PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
				if (inputSystem.GetKeyState(GLFW_KEY_Z)) {

					playerBody->forceManager.ApplyToForce(Vec2(0.0f, 0.1f), 20.f, 0.3f, FORCE_INDEX::EXTERNAL);
				}
				if (inputSystem.GetKeyState(GLFW_KEY_J)) {

					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(-playerBody->direction, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				else if (inputSystem.GetKeyState(GLFW_KEY_U)) {

					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(playerBody->direction, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}
				else {

					playerBody->forceManager.DeactivateForce(FORCE_INDEX::INTERNAL);
				}
				if (inputSystem.GetKeyState(GLFW_KEY_H)) {
					//playerBody->currentRotationSpeed = playerBody->rotationSpeed;
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(-playerBody->direction.y, playerBody->direction.x), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
					//physicsSys->SetCurrentRotationSpeed(GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed, 0);
				}
				if (inputSystem.GetKeyState(GLFW_KEY_K)) {
					//playerBody->currentRotationSpeed = -playerBody->rotationSpeed;
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					//playerBody->forceManager.SetDirection(Vec2(1,0), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(-Vec2(-playerBody->direction.y, playerBody->direction.x), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
					//physicsSys->SetCurrentRotationSpeed(-(GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed), 0);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_A) && inputSystem.GetKeyState(GLFW_KEY_D)) || (!inputSystem.GetKeyState(GLFW_KEY_A) && !inputSystem.GetKeyState(GLFW_KEY_D))) {
					playerBody->currentRotationSpeed = 0;
					//physicsSys->SetCurrentRotationSpeed(0, 0);
				}
			}
			/*
			if (physBod->forceManager.forceVec.size() >= 1) {
				
				if (tx->position.x < -800) {
					physBod->forceManager.SetActive(true, FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetDirection(Vec2(1.f, 0), FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetMagnitude(physBod->speed, FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetLifetime(3.f, FORCE_INDEX::EXTERNAL);
				}
				else if (tx->position.x > 800) {
					physBod->forceManager.SetActive(true, FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetDirection(Vec2(-1.f, 0), FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetMagnitude(physBod->speed, FORCE_INDEX::EXTERNAL);
					physBod->forceManager.SetLifetime(3.f, FORCE_INDEX::EXTERNAL);
				}	
				else {
					if (physBod->forceManager.forceVec[FORCE_INDEX::EXTERNAL]->isActive == false) {
						physBod->forceManager.SetActive(true, FORCE_INDEX::EXTERNAL);
						physBod->forceManager.SetDirection(Vec2(-1.f, 0), FORCE_INDEX::EXTERNAL);
						physBod->forceManager.SetMagnitude(physBod->speed, FORCE_INDEX::EXTERNAL);
						physBod->forceManager.SetLifetime(1.f, FORCE_INDEX::EXTERNAL);
					}
				}
			}*/
			
		}
	};

	void End() {}
	~TestScript() {}
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
			PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
			if (inputSystem.GetKeyState(GLFW_KEY_Z)) {
				
				playerBody->forceManager.ApplyToForce(Vec2(0.0f, 0.1f), 20.f, 0.3f, FORCE_INDEX::EXTERNAL);
			}
			if (inputSystem.GetKeyState(GLFW_KEY_S)) {
				
				playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetDirection(-playerBody->direction, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
			}
			
			else if (inputSystem.GetKeyState(GLFW_KEY_W)) {
				
				playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetDirection(playerBody->direction, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
			}
			else {
				
				playerBody->forceManager.DeactivateForce(FORCE_INDEX::INTERNAL);
			}
			if (inputSystem.GetKeyState(GLFW_KEY_A)) {
				//playerBody->currentRotationSpeed = playerBody->rotationSpeed;
				playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetDirection(Vec2(-playerBody->direction.y, playerBody->direction.x),FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				//physicsSys->SetCurrentRotationSpeed(GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed, 0);
			}
			if (inputSystem.GetKeyState(GLFW_KEY_D)) {
				//playerBody->currentRotationSpeed = -playerBody->rotationSpeed;
				playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
				//playerBody->forceManager.SetDirection(Vec2(1,0), FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetDirection(-Vec2(-playerBody->direction.y, playerBody->direction.x), FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
				playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				//physicsSys->SetCurrentRotationSpeed(-(GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed), 0);
			}

			if ((inputSystem.GetKeyState(GLFW_KEY_A) && inputSystem.GetKeyState(GLFW_KEY_D)) || (!inputSystem.GetKeyState(GLFW_KEY_A) && !inputSystem.GetKeyState(GLFW_KEY_D))) {
				playerBody->currentRotationSpeed = 0;
				//physicsSys->SetCurrentRotationSpeed(0, 0);
			}
		}
	};

	void End() {}
	~TestScript2() {}
};