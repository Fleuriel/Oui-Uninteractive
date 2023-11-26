#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"

class inventory {
public:
	GameObject* knife = objectFactory->GetGameObjectByID(0);
	GameObject* rifle = objectFactory->GetGameObjectByID(1);
	GameObject* pistol = objectFactory->GetGameObjectByID(2);
	GameObject* bag[3] = { knife, rifle, pistol };
};

class inventory2 {
public:
	PhysicsBody* playerBodyFirst = GET_COMPONENT(inventory().bag[0], PhysicsBody, ComponentType::PHYSICS_BODY);
	PhysicsBody* playerBodySecond = GET_COMPONENT(inventory().bag[1], PhysicsBody, ComponentType::PHYSICS_BODY);
	PhysicsBody* playerBodyThird = GET_COMPONENT(inventory().bag[2], PhysicsBody, ComponentType::PHYSICS_BODY);
	PhysicsBody* Bodies[3] = { playerBodyFirst, playerBodySecond, playerBodyThird };
};



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

				//Flags initializers
				static bool count = false;
				static bool pickedup = false;

				//Set playerBody1 as the player (permanent)
				GameObject* player = objectFactory->GetGameObjectByName("JSONPlayer");
				if (player != nullptr) {
					PhysicsBody* playerBody1 = GET_COMPONENT(player, PhysicsBody, ComponentType::PHYSICS_BODY);
					//Declare a temporary physics body for the final weapon chosen
					if (playerBody1 != nullptr) {
	
						static PhysicsBody* playerBodyFinale = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);
						if (playerBodyFinale != nullptr) {
							//Checking key pressed to enable weapon pickup / drop off
							if (inputSystem.GetKeyState(GLFW_KEY_X)) {
								count = 0;
								pickedup = false;

							}
							if (inputSystem.GetKeyState(GLFW_KEY_C)) {
								count = 1;
								pickedup = true;
							}

							if (pickedup == false) {
								int closestID = 0;
								float closestDistance = 0;
								bool initialized = false;
								for (int i = 0; i < 3; i++) {
									if (inventory2().Bodies[i] != nullptr) {
										float tempo = Vector2DDistance(inventory2().Bodies[i]->txPtr->position, playerBody1->txPtr->position);

										if (tempo < closestDistance || initialized == false) {
											initialized = true;
											closestDistance = tempo;
											closestID = i;
										}
									}
									else {
										continue;
									}
									
								}
								playerBodyFinale = inventory2().Bodies[closestID];
							}

							if (count == 1) {
								if (playerBodyFinale != nullptr && playerBody1 != nullptr) {
									if (playerBodyFinale->txPtr != nullptr && playerBody1->txPtr != nullptr) {
										playerBodyFinale->txPtr->position.x = playerBody1->txPtr->position.x + 30;
										playerBodyFinale->txPtr->position.y = playerBody1->txPtr->position.y - 20;
									}
									
								}
							
							}
						}
						
					}
						
					}
			}
		}

	};

	void End() {}
	~WeaponPickupScript() {}
};