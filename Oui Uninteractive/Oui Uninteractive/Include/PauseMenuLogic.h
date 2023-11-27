/**************************************************************************
 * @file PauseMenuLogic.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-11-2023
 * @brief This file contains the declaration of the PauseMenuLogic class
 *		  which is a subset of IScript to enable logic of pause
 *************************************************************************/



#include "IScript.h"
#include "Logic.h"
#include "SceneManager.h"
#include "ObjectFactory.h" 
#include "Collision.h"
#include "Background.h"
/**************************************************************************
 * @file PauseMenuLogic.h
 * @author CHEAH Tristan Tze Hong - 100%
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 02-11-2023
 * @brief This file contains the definition of a Script containing the logic 
 *		  for the Pause Menu
 *************************************************************************/
class PauseMenuLogic : public IScript {
	public:
		/**************************************************************************
		* @brief Constructor
		*************************************************************************/
		PauseMenuLogic(std::string newName, bool gameplayFlag) : IScript(newName, gameplayFlag) {}
		/**************************************************************************
		* @brief Initialize function for Pause Menu Logic script
		* @return void
		*************************************************************************/
		void Initialize() {
		
			logicSystem->AddLogicScript(this);
			
		}
		/**************************************************************************
		* @brief Update function for Pause Menu Logic script
			if (sysManager->isPaused) {
				double mouseY; // = io.MousePos.y;
				glfwGetCursorPos(windowNew, &mouseX, &mouseY);				
				background.SetBackGround(assetManager.GetTexture("GreenBG1920"));
				if (Editor::editorOn)
					OpenGLObject::FrameBufferMouseCoords(windowNew, &mouseX, &mouseY, OpenGLObject::cameraObject);
				else
					OpenGLObject::windowMouseCoords(windowNew, &mouseX, &mouseY, OpenGLObject::cameraObject);

				GameObject* gObj = objectFactory->GetGameObjectByID(gameObjectID);
				if (gObj != nullptr) {
					Transform* tx = GET_COMPONENT(gObj, Transform, ComponentType::TRANSFORM);
					if (tx != nullptr) {
						if (gObj->GetType() == "PauseMenu") {
							if (gObj->GetName() == "Resume") {
								//position game object in camera
								tx->scale = Vec2(windowSize.first / 4.f, windowSize.second / 8.f);
								tx->position = Vec2(-windowSize.first/4.f ,0);
								//fontManager->RenderText("Valoon.ttf", "Resume Game", tx->position.x + windowSize.first/16.f, tx->position.y, 1.0f, glm::vec3(0.4, 0.7, 0.9));

							}
							else if (gObj->GetName() == "Quit") {
								tx->scale = Vec2(windowSize.first / 4.f, windowSize.second / 8.f);
								tx->position = Vec2(windowSize.first / 4.f, 0);
								//fontManager->RenderText("Valoon.ttf", "Quit Game", tx->position.x - windowSize.first / 16.f, tx->position.y, 1.0f, glm::vec3(0.4, 0.7, 0.9));
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
		/**************************************************************************
		* @brief End function for Pause Menu Logic script
		* @return void
		*************************************************************************/
		void End() {}
};