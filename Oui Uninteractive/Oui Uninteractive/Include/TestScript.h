#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"



class TestScript : public IScript {
public:
	TestScript(std::string newName) : IScript(newName) {
		
	};
	void Initialize() {
		logicSystem->AddLogicScript(this);
	};

	void Update(size_t gameObjectID) {
		GameObject* gObj = objectFactory->GetGameObjectByID(gameObjectID);
		if (gObj != nullptr) {
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
						playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
						playerBody->forceManager.SetDirection(Vec2(-playerBody->direction.y, playerBody->direction.x), FORCE_INDEX::INTERNAL);
						playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
						playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
					}
					if (inputSystem.GetKeyState(GLFW_KEY_K)) {
						playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
						playerBody->forceManager.SetDirection(-Vec2(-playerBody->direction.y, playerBody->direction.x), FORCE_INDEX::INTERNAL);
						playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
						playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
					}

					if ((inputSystem.GetKeyState(GLFW_KEY_A) && inputSystem.GetKeyState(GLFW_KEY_D)) || (!inputSystem.GetKeyState(GLFW_KEY_A) && !inputSystem.GetKeyState(GLFW_KEY_D))) {
						playerBody->currentRotationSpeed = 0;
					}
				}
			}
		}
		
	};

	void End() {}
	~TestScript() {}
};

class TestScript2 : public IScript {
public:
	TestScript2(std::string newName) : IScript(newName) {

	};
	void Initialize() {
		logicSystem->AddLogicScript(this);
	};

	void Update(size_t gameObjectID) {
		GameObject* gObj = objectFactory->GetGameObjectByID(gameObjectID);
		if (gObj != nullptr) {
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
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(-playerBody->direction.y, playerBody->direction.x), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}
				if (inputSystem.GetKeyState(GLFW_KEY_D)) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(-Vec2(-playerBody->direction.y, playerBody->direction.x), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}
				if ((inputSystem.GetKeyState(GLFW_KEY_A) && inputSystem.GetKeyState(GLFW_KEY_D)) || (!inputSystem.GetKeyState(GLFW_KEY_A) && !inputSystem.GetKeyState(GLFW_KEY_D))) {
					playerBody->currentRotationSpeed = 0;
				}
				if ((inputSystem.GetKeyState(GLFW_KEY_W) && inputSystem.GetKeyState(GLFW_KEY_D))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(1, 1), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_W) && inputSystem.GetKeyState(GLFW_KEY_A))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(-1, 1), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_S) && inputSystem.GetKeyState(GLFW_KEY_D))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(1, -1), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_S) && inputSystem.GetKeyState(GLFW_KEY_A))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(-1, -1), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_W) && inputSystem.GetKeyState(GLFW_KEY_S))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(0, 0), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_W) && inputSystem.GetKeyState(GLFW_KEY_S) && inputSystem.GetKeyState(GLFW_KEY_D))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(1, 0), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_W) && inputSystem.GetKeyState(GLFW_KEY_S) && inputSystem.GetKeyState(GLFW_KEY_A))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(-1, 0), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_A) && inputSystem.GetKeyState(GLFW_KEY_D))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(0, 0), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_A) && inputSystem.GetKeyState(GLFW_KEY_D) && inputSystem.GetKeyState(GLFW_KEY_W))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(0, 1), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_A) && inputSystem.GetKeyState(GLFW_KEY_D) && inputSystem.GetKeyState(GLFW_KEY_S))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(0, -1), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}

				if ((inputSystem.GetKeyState(GLFW_KEY_A) && inputSystem.GetKeyState(GLFW_KEY_D) && inputSystem.GetKeyState(GLFW_KEY_S) && inputSystem.GetKeyState(GLFW_KEY_W))) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetDirection(Vec2(0, 0), FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);
				}
			}
		}
		
	};

	void End() {}
	~TestScript2() {}
};

class TestScript3 : public IScript {
public:
	TestScript3(std::string newName) : IScript(newName) {

	};
	void Initialize() {
		logicSystem->AddLogicScript(this);
	};

	void Update(size_t gameObjectID) {
		GameObject* gObj = objectFactory->GetGameObjectByID(gameObjectID);
		if (gObj != nullptr) {
			Transform* tx = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM);
			PhysicsBody* physBod = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
			if (tx != nullptr && physBod != nullptr) {
				if (tx != nullptr && physBod != nullptr) {
					PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
					static bool count = false;
					if (count == true) {

						PhysicsBody* playerBody1 = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);

						playerBody->txPtr->position.x = playerBody1->txPtr->position.x + 30;
						playerBody->txPtr->position.y = playerBody1->txPtr->position.y - 20;
						//playerBody->forceManager.ApplyToForce(Vec2(0.0f, 0.1f), 20.f, 0.3f, FORCE_INDEX::EXTERNAL);
					}

					if (inputSystem.GetKeyState(GLFW_KEY_X)) {
						count = 0;
					}
					if (inputSystem.GetKeyState(GLFW_KEY_C)) {
						count = 1;
					}

					/*if (inputSystem.GetKeyState(GLFW_KEY_X)) {
						if (count == false) {
							count = true;
						}
						else {
							count = false;
						} 
						//count = !count;
					}*/



				}
			}
		}

	};

	void End() {}
	~TestScript3() {}
};