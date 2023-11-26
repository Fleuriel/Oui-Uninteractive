#include "IScript.h"
#include "Logic.h"
#include "SceneManager.h"
#include "ObjectFactory.h"
#include "Collision.h"
class PauseMenuLogic : public IScript {
	public:
		PauseMenuLogic(std::string newName) : IScript(newName) {}
		void Initialize() {
			logicSystem->AddLogicScript(this);
		}
		void Update(size_t gameObjectID) {
			if (sysManager->isPaused) {
				double mouseX; // = io.MousePos.x;
				double mouseY; // = io.MousePos.y;

				glfwGetCursorPos(windowNew, &mouseX, &mouseY);

				OpenGLObject::FrameBufferMouseCoords(windowNew, &mouseX, &mouseY, OpenGLObject::cameraObject);
				GameObject* gObj = objectFactory->GetGameObjectByID(gameObjectID);
				if (gObj != nullptr) {
					Transform* tx = GET_COMPONENT(gObj, Transform, ComponentType::TRANSFORM);
					if (tx != nullptr) {
						if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) && CollisionPointRotateRect(tx->position, tx->scale.x, tx->scale.y, mouseX, mouseY, tx->rotation)) {
							if (objectFactory->GetGameObjectByID(gameObjectID)->GetType() == "PauseMenu") {
								if (objectFactory->GetGameObjectByID(gameObjectID)->GetName() == "Resume") {
									//position game object in camera
								}
								else if (objectFactory->GetGameObjectByID(gameObjectID)->GetName() == "Quit") {
									sceneManager->currSceneID = STATE_QUIT;
								}
							}
						}
					}
					
				}
				
			}
			
		}
		void End() {}
};