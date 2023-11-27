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
						tx->position = Vec2(OpenGLObject::cameraObject.posX, OpenGLObject::cameraObject.posY - windowSize.second / 2.f);
					}
					if (gObj->GetName() == "InventoryObject1") {
						//position game object in camera
						tx->position = Vec2(OpenGLObject::cameraObject.posX + windowSize.first / 6.f, OpenGLObject::cameraObject.posY - windowSize.second / 2.f);

					}
					else if (gObj->GetName() == "InventoryObject2") {
						//position game object in camera
						tx->position = Vec2(OpenGLObject::cameraObject.posX + windowSize.first / 3.3f, OpenGLObject::cameraObject.posY - windowSize.second / 2.f);

					}
					else if (gObj->GetName() == "InventoryObject3") {
						//position game object in camera
						tx->position = Vec2(OpenGLObject::cameraObject.posX + windowSize.first / 2.3f, OpenGLObject::cameraObject.posY - windowSize.second / 2.f);

					}
					else if (gObj->GetName() == "InventoryObject4") {
						//position game object in camera
						tx->position = Vec2(OpenGLObject::cameraObject.posX + windowSize.first / 1.75f, OpenGLObject::cameraObject.posY - windowSize.second / 2.f);
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
	
	};

	
	void End() {}
};
