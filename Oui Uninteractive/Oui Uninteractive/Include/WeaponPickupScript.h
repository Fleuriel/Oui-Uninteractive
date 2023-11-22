#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"

class WeaponPickupScript : public IScript {
public:
	WeaponPickupScript(std::string newName) : IScript(newName) {

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
					//Set playerBody1 as the player
					PhysicsBody* playerBody1 = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);

					//Set playerBody as the knife
					PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(1), PhysicsBody, ComponentType::PHYSICS_BODY);
					int tempo = Vector2DDistance(playerBody->txPtr->position, playerBody1->txPtr->position);

					//Declare a temporary physics body
					PhysicsBody* playerBodyZ;
					PhysicsBody* playerBodyFinale;

					for (int i = 2; i < 3; i++) {

						//Set playerBodyZ as the weapon after knife
						playerBodyZ = GET_COMPONENT(objectFactory->GetGameObjectByID(i), PhysicsBody, ComponentType::PHYSICS_BODY);
						int tempo2 = Vector2DDistance(playerBodyZ->txPtr->position, playerBody1->txPtr->position);

						if (tempo < tempo2) {
							playerBodyFinale = playerBody;
						}
						else {
							playerBodyFinale = playerBodyZ;
						}

					}
					//PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(7), PhysicsBody, ComponentType::PHYSICS_BODY);
					static bool count = false;
					if (count == true) {

						//PhysicsBody* playerBody1 = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);

						playerBodyFinale->txPtr->position.x = playerBody1->txPtr->position.x + 30;
						playerBodyFinale->txPtr->position.y = playerBody1->txPtr->position.y - 20;
						//playerBody->forceManager.ApplyToForce(Vec2(0.0f, 0.1f), 20.f, 0.3f, FORCE_INDEX::EXTERNAL);
					}

					if (inputSystem.GetKeyState(GLFW_KEY_X)) {
						count = 0;
					}
					if (inputSystem.GetKeyState(GLFW_KEY_C)) {
						count = 1;
					}
				}
			}
		}

	};

	void End() {}
	~WeaponPickupScript() {}
};