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

					static bool count = false;
					static bool pickedup = false;
					int z = 1;

					if (inputSystem.GetKeyState(GLFW_KEY_X)) {
						count = 0;
						pickedup = false;

					}
					if (inputSystem.GetKeyState(GLFW_KEY_C)) {
						count = 1;
						pickedup = true;
					}

					//Set playerBody1 as the player (permanent)
					PhysicsBody* playerBody1 = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);

					//Declare a temporary physics body for the final weapon chosen
					static PhysicsBody* playerBodyFinale = GET_COMPONENT(objectFactory->GetGameObjectByID(1), PhysicsBody, ComponentType::PHYSICS_BODY);

					
					if (pickedup == false) {
						for (int i = 2; i < 4; i++) {
							
							//knife
							PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(z), PhysicsBody, ComponentType::PHYSICS_BODY);
							int tempo = Vector2DDistance(playerBody->txPtr->position, playerBody1->txPtr->position);
							//Set playerBodyZ as the weapon after knife
						    PhysicsBody* playerBodyZ = GET_COMPONENT(objectFactory->GetGameObjectByID(i), PhysicsBody, ComponentType::PHYSICS_BODY);
							int tempo2 = Vector2DDistance(playerBodyZ->txPtr->position, playerBody1->txPtr->position);
							
							if (tempo < tempo2) {
								playerBodyFinale = playerBody;
							}
							else {
								playerBodyFinale = playerBodyZ;
								tempo = tempo2;
								playerBody = playerBodyZ;
								z++;
							}
							
						}
					}

					if (count == 1) {
						playerBodyFinale->txPtr->position.x = playerBody1->txPtr->position.x + 30;
						playerBodyFinale->txPtr->position.y = playerBody1->txPtr->position.y - 20;
					}


				}
			}
		}

	};

	void End() {}
	~WeaponPickupScript() {}
};