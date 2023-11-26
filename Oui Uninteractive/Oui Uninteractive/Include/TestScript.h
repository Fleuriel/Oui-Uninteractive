#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"


class TestScript : public IScript {
public:
	TestScript(std::string newName, bool gameplayFlag) : IScript(newName, gameplayFlag) {
		
	};
	void Initialize() {
		if (isGameplay) {
			logicSystem->AddLogicScript(this);
		}
		else {
			logicSystem->AddLogicScriptToPaused(this);
		}
		
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
	TestScript2(std::string newName, bool gameplayFlag) : IScript(newName, gameplayFlag) {

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
					//playerBody->forceManager.SetDirection(-playerBody->direction, FORCE_INDEX::INTERNAL);
					playerBody->direction.x = 0;
					playerBody->direction.y = -1;
					playerBody->forceManager.SetDirection(playerBody->direction, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);

					objectFactory->GetGameObjectByID(gameObjectID)->GetSpriteDirection(playerBody->direction.x, playerBody->direction.y);
				}

				else if (inputSystem.GetKeyState(GLFW_KEY_W)) {

					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					//playerBody->forceManager.SetDirection(playerBody->direction, FORCE_INDEX::INTERNAL);
					playerBody->direction.x = 0;
					playerBody->direction.y = 1;
					playerBody->forceManager.SetDirection(playerBody->direction, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);

					objectFactory->GetGameObjectByID(gameObjectID)->GetSpriteDirection(playerBody->direction.x, playerBody->direction.y);
				}
				else {

					playerBody->forceManager.DeactivateForce(FORCE_INDEX::INTERNAL);
				}
				if (inputSystem.GetKeyState(GLFW_KEY_A)) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->direction.x = -1;
					playerBody->direction.y = 0;
					playerBody->forceManager.SetDirection(playerBody->direction, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);

					objectFactory->GetGameObjectByID(gameObjectID)->GetSpriteDirection(playerBody->direction.x, playerBody->direction.y);
				}
				if (inputSystem.GetKeyState(GLFW_KEY_D)) {
					playerBody->forceManager.SetActive(true, FORCE_INDEX::INTERNAL);
					playerBody->direction.x = 1;
					playerBody->direction.y = 0;
					playerBody->forceManager.SetDirection(playerBody->direction, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetMagnitude(playerBody->speed, FORCE_INDEX::INTERNAL);
					playerBody->forceManager.SetLifetime(0.2f, FORCE_INDEX::INTERNAL);

					objectFactory->GetGameObjectByID(gameObjectID)->GetSpriteDirection(playerBody->direction.x, playerBody->direction.y);
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