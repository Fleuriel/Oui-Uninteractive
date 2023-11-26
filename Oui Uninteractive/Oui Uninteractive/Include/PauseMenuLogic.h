#include "IScript.h"
#include "Logic.h"
#include "SceneManager.h"
#include "ObjectFactory.h" 
#include "Collision.h"
#include "Background.h"
class PauseMenuLogic : public IScript {
	public:
		PauseMenuLogic(std::string newName, bool gameplayFlag) : IScript(newName, gameplayFlag) {}
		void Initialize() {
		
			logicSystem->AddLogicScript(this);
			
		}
		void Update(size_t gameObjectID) {
			fontManager->RenderText("Next_Sunday.ttf", "Resume", 500, 500, 1.0f, glm::vec3(236.0f / 255.0f, 1.0f, 220.0f / 255.0f));
			if (sysManager->isPaused) {
				double mouseX; // = io.MousePos.x;
				double mouseY; // = io.MousePos.y;

				glfwGetCursorPos(windowNew, &mouseX, &mouseY);
				background.SetBackGround(assetManager.GetTexture("GreenBG1920"));
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
			else {
				background.SetBackGround(assetManager.GetTexture("newbackground"));
			}
			
		}
		void End() {}
};