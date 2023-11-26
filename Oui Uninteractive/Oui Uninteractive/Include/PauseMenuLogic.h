#include "IScript.h"
#include "Logic.h"
#include "SceneManager.h"
#include "ObjectFactory.h" 
#include "Collision.h"
class PauseMenuLogic : public IScript {
	public:
		PauseMenuLogic(std::string newName, bool gameplayFlag) : IScript(newName, gameplayFlag) {}
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
						if (gObj->GetType() == "PauseMenu") {
							if (gObj->GetName() == "Resume") {
								//position game object in camera
								tx->position = Vec2(OpenGLObject::cameraObject.posX - Editor::gameWindowSize.first / 4.f, OpenGLObject::cameraObject.posY);
							}
							else if (gObj->GetName() == "Quit") {
								tx->position = Vec2(OpenGLObject::cameraObject.posX + Editor::gameWindowSize.first / 4.f , OpenGLObject::cameraObject.posY);
							}
						}
						if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) && CollisionPointRotateRect(tx->position, tx->scale.x, tx->scale.y, mouseX, mouseY, tx->rotation)) {
							if (gObj->GetType() == "PauseMenu") {
								if (gObj->GetName() == "Resume") {
									//position game object in camera
									sysManager->isPaused = false;
								}
								else if (gObj->GetName() == "Quit") {
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