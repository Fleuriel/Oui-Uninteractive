#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"
#include "Background.h"
#include "Input.h"
class InventoryMenuLogic : public IScript {
public:
	std::vector<std::string> slotVec;
	bool initialised;
	InventoryMenuLogic(std::string newName, bool gameplayFlag) : IScript(newName, gameplayFlag) {}
	void Initialize() {

		logicSystem->AddLogicScript(this);
		initialised = false;
	}
	void Update(size_t gameObjectID) {
		if (initialised == false) {
			//gObj = 
			slotVec.push_back("InventoryObject1");

			//gObj = 
			slotVec.push_back("InventoryObject2");

			//gObj = 
			slotVec.push_back("InventoryObject3");

			//gObj =
			slotVec.push_back("InventoryObject4");

			initialised = true;
		}
		
		for (std::string str : slotVec) {
			
			GameObject* gObj = objectFactory->GetGameObjectByName(str);
			if (gObj != nullptr)
			{
				Transform* tx = GET_COMPONENT(gObj, Transform, ComponentType::TRANSFORM);
				if (tx != nullptr) {
					if (gObj->GetName() == "Background2") {
						tx->position = Vec2(OpenGLObject::cameraObject.posX - Editor::gameWindowSize.first + 1262.f, OpenGLObject::cameraObject.posY - Editor::gameWindowSize.second / 2.f);
					}
					if (gObj->GetName() == "InventoryObject1") {
						//position game object in camera
						tx->position = Vec2(OpenGLObject::cameraObject.posX + Editor::gameWindowSize.first / 6.f, OpenGLObject::cameraObject.posY - Editor::gameWindowSize.second / 2.f);

					}
					else if (gObj->GetName() == "InventoryObject2") {
						//position game object in camera
						tx->position = Vec2(OpenGLObject::cameraObject.posX + Editor::gameWindowSize.first / 3.3f, OpenGLObject::cameraObject.posY - Editor::gameWindowSize.second / 2.f);

					}
					else if (gObj->GetName() == "InventoryObject3") {
						//position game object in camera
						tx->position = Vec2(OpenGLObject::cameraObject.posX + Editor::gameWindowSize.first / 2.3f, OpenGLObject::cameraObject.posY - Editor::gameWindowSize.second / 2.f);

					}
					else if (gObj->GetName() == "InventoryObject4") {
						//position game object in camera
						tx->position = Vec2(OpenGLObject::cameraObject.posX + Editor::gameWindowSize.first / 1.75f, OpenGLObject::cameraObject.posY - Editor::gameWindowSize.second / 2.f);
					}
				}
			}
			
				
			
		
		}

		GameObject* player = objectFactory->GetGameObjectByName("JSONPlayer");
		if (player != nullptr) {
			InventoryComponent* inv = GET_COMPONENT(player, InventoryComponent, ComponentType::INVENTORY);
			if (inv != nullptr) {
				int index = 0;
				for (std::string str : inv->Inventory) {

					if (str == "Knife") {
						GameObject* gObj = objectFactory->GetGameObjectByName(slotVec[index]);
						if (gObj != nullptr) {
							gObj->SetTexture("Knife(Weapon)");
						}
					}
					else if (str == "Pistol") {
						GameObject* gObj = objectFactory->GetGameObjectByName(slotVec[index]);
						if (gObj != nullptr) {
							gObj->SetTexture("Pistol(Weapon)");
						}
					}
					else if (str == "Rifle") {
						GameObject* gObj = objectFactory->GetGameObjectByName(slotVec[index]);
						if (gObj != nullptr) {
							gObj->SetTexture("Rifle(Weapon)");
						}
					}


					index++;
					if (index > slotVec.size() - 1) {
						break;
					}

				}
			}
		}
		
		//if (gObj != nullptr) {
		//	Transform* tx = GET_COMPONENT(gObj, Transform, ComponentType::TRANSFORM);
		//	if (tx != nullptr) {

		//		if (gObj->GetName() == "Background2") {
		//			tx->position = Vec2(OpenGLObject::cameraObject.posX - Editor::gameWindowSize.first + 1262.f, OpenGLObject::cameraObject.posY -Editor::gameWindowSize.second / 2.f);
		//			
		//		}
		//		if (gObj->GetType() == "InventoryObject") {
		//			if (gObj->GetName() == "InventoryObject1") {
		//				//position game object in camera
		//				tx->position = Vec2(OpenGLObject::cameraObject.posX + Editor::gameWindowSize.first / 6.f, OpenGLObject::cameraObject.posY - Editor::gameWindowSize.second / 2.f);
		//				slotVec[0] = tx->position;
		//			}
		//			else if (gObj->GetName() == "InventoryObject2") {
		//				//position game object in camera
		//				tx->position = Vec2(OpenGLObject::cameraObject.posX + Editor::gameWindowSize.first / 3.3f, OpenGLObject::cameraObject.posY - Editor::gameWindowSize.second / 2.f);
		//				slotVec[1] = tx->position;
		//			}
		//			else if (gObj->GetName() == "InventoryObject3") {
		//				//position game object in camera
		//				tx->position = Vec2(OpenGLObject::cameraObject.posX + Editor::gameWindowSize.first / 2.3f, OpenGLObject::cameraObject.posY - Editor::gameWindowSize.second / 2.f);
		//				slotVec[2] = tx->position;
		//			}
		//			else if (gObj->GetName() == "InventoryObject4") {
		//				//position game object in camera
		//				tx->position = Vec2(OpenGLObject::cameraObject.posX + Editor::gameWindowSize.first / 1.75f, OpenGLObject::cameraObject.posY - Editor::gameWindowSize.second / 2.f);
		//				slotVec[3] = tx->position;
		//			}
		//		}

		//		
		//		
		//		

		//		float pickuprange = 50.f;
		//		//if (gObj->GetType() == "Weapon") {
		//		//	if (gObj->GetName() == "Rifle") {
		//		//		//Vector2DDistance(tx->position);
		//		//	}

		//		//}
		//		static int i = 0;

		//		/*if (inputSystem.GetKeyState(GLFW_KEY_C)) {
		//			i = 2;
		//		}

		//		if (i > 1) {
		//			if (gObj->GetName() == "Rifle")
		//				tx->position = slot2;

		//			if (gObj->GetName() == "Pistol")
		//				tx->position = slot3;

		//			if (gObj->GetName() == "Knife")
		//				tx->position = slot1;
		//		}*/
		//	}
		//}


	};

	
	void End() {}
};
