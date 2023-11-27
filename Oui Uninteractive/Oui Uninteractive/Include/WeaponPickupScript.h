/**************************************************************************
* @file WeaponPickupScript.h
* @author QUEK Cheng Kwang, Emery - 100%
* @par DP email: c.quek@digipen.edu
* @par Course:	CSD 2401
* @par Software Engineering Project 3
* @date 26-11-2023
* @brief This file contains the script for picking up weapon objects
*************************************************************************/

#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"
#include "Background.h"
#include "InventoryComponent.h"

 //class inventory {
 //public:
 //	GameObject* knife = objectFactory->GetGameObjectByID(0);
 //	GameObject* rifle = objectFactory->GetGameObjectByID(1);
 //	GameObject* pistol = objectFactory->GetGameObjectByID(2);
 //	GameObject* bag[3] = { knife, rifle, pistol };
 //};
 //
 //class inventory2 {
 //public:
 //	PhysicsBody* playerBodyFirst = GET_COMPONENT(inventory().bag[0], PhysicsBody, ComponentType::PHYSICS_BODY);
 //	PhysicsBody* playerBodySecond = GET_COMPONENT(inventory().bag[1], PhysicsBody, ComponentType::PHYSICS_BODY);
 //	PhysicsBody* playerBodyThird = GET_COMPONENT(inventory().bag[2], PhysicsBody, ComponentType::PHYSICS_BODY);
 //	PhysicsBody* Bodies[3] = { playerBodyFirst, playerBodySecond, playerBodyThird };
 //};

class WeaponPickupScript : public IScript {
public:
	bool initialized;
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	WeaponPickupScript(std::string newName, bool gameplayFlag) : IScript(newName, gameplayFlag) {
		initialized = false;
	};
	/**************************************************************************
	* @brief Initialize the WeaponPickup script
	* @return void
	*************************************************************************/
	void Initialize() {
		logicSystem->AddLogicScript(this);
		ComponentFactory<InventoryComponent>* cfPtr{ new ComponentFactory<InventoryComponent>(ComponentType::INVENTORY) };
		objectFactory->AddComponentFactory(ComponentType::INVENTORY, cfPtr);
	};
	/**************************************************************************
	* @brief Update the WeaponPickup script
	* @return void
	*************************************************************************/
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
					//Player's physics body
					//Transform* playerBody1 = GET_COMPONENT(player, Transform, ComponentType::);
				InventoryComponent* playerInventory = GET_COMPONENT(player, InventoryComponent, ComponentType::INVENTORY);
					//Declare a temporary physics body for the final weapon chosen
					if (tx != nullptr && playerInventory != nullptr) {

						//Checking key pressed to enable weapon pickup / drop off
						if (inputSystem.GetKeyState(GLFW_KEY_X)) {
							count = 1;
							int closestID = -1;
							float closestDistance = 0;
							//bool initialized = false;

							std::map<size_t, GameObject*> copy = objectFactory->GetGameObjectIDMap();
							for (std::map<size_t, GameObject*>::iterator it = copy.begin(); it != copy.end(); it++) {
								if (it->second->GetType() == "Weapon") {
									Transform* xform = GET_COMPONENT(it->second, Transform, ComponentType::TRANSFORM);
									if (xform != nullptr) {
										float tempo = Vector2DDistance(tx->position, xform->position);
										if (tempo < closestDistance || initialized == false) {
											
											initialized = true;
											closestDistance = tempo;
											closestID = static_cast<int>(xform->GetOwner()->GetGameObjectID());

										}
									}
								}
							}
							if (objectFactory->GetGameObjectByID(closestID) != nullptr) {
								std::vector<std::string>::iterator it = playerInventory->Inventory.begin();
								if (std::find(playerInventory->Inventory.begin(), playerInventory->Inventory.end(), objectFactory->GetGameObjectByID(closestID)->GetName()) == 
									std::end(playerInventory->Inventory)) {
									playerInventory->Inventory.push_back(objectFactory->GetGameObjectByID(closestID)->GetName());
									playerInventory->currentWeaponID = closestID;
								}
								
							}
							pickedup = false;

						}
						//Offset the amount of distance 
						//if (playerInventory->Inventory.size() >= 1) {
						//	Transform* pBodyFinale = GET_COMPONENT(playerInventory->Inventory[playerInventory->currentWeaponID], 
						//		Transform, ComponentType::TRANSFORM);//objectFactory->GetGameObjectByID(playerInventory->currentWeaponID), Transform, ComponentType::TRANSFORM);
						//	if (pBodyFinale != nullptr && tx != nullptr) {
						//		pBodyFinale->position.x = tx->position.x + 30;
						//		pBodyFinale->position.y = tx->position.y - 20;
						//	}
						//}
						}

						//While there's no pickup, check for the closest object to the player
						
							
						
					
				}
			}
		}
		initialized = false;
	};

	/**************************************************************************
	* @brief End the WeaponPickup script
	* @return void
	*************************************************************************/
	void End() {}
	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~WeaponPickupScript() {
		initialized = false;
	}
};