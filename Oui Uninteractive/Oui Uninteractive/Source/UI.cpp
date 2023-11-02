/**************************************************************************
 * @file UI.cpp
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-10-2023
 * @brief This source file contains the definition of the UI class used to and handle UI functionality within the game
 *************************************************************************/

#include "UI.h"

UIManager* uiManager = nullptr;


/**************************************************************************
* @brief Default constructor for UIManager class
*************************************************************************/
UIManager::UIManager() {
	if (uiManager != nullptr) {
		// Instantiate UI system
		return;
	}
	else {
		uiManager = this;
	}
}


/**************************************************************************
* @brief Initializer for UIManager class
* @return No return
*************************************************************************/
void UIManager::Initialize() {
	std::cout << "UI INIT" << std::endl;
	test = false;
}


/**************************************************************************
* @brief Update function for the UIManager class
* @param dt - delta time
* @return No return
*************************************************************************/
void UIManager::Update(float dt) {
	// Start time profiling for sound system
	//TimeProfiler profiler(Editor::timeRecorder.soundTime);
	
	if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_LEFT)) {
		std::pair<double, double> convertedMousePos;
		double mouseX, mouseY;
		glfwGetCursorPos(windowNew, &mouseX, &mouseY);
		convertedMousePos.first = mouseX;
		convertedMousePos.second = mouseY;

		

		//float gameWindowMouseX = mouseX - Editor::gameWindowOrigin.first;
		//float gameWindowMouseY = mouseY - Editor::gameWindowOrigin.second;
		//convertedMousePos.first = gameWindowMouseX - Editor::gameWindowSize.first * 0.5f;
		//convertedMousePos.second = (Editor::gameWindowSize.second * 0.5f) - gameWindowMouseY;

		//std::cout << "converted pos: " << convertedMousePos.first << ", " << convertedMousePos.second << std::endl;
		//std::cout << Editor::gameWindowSize.first << ", " << Editor::gameWindowSize.second << std::endl;

		std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
		std::map<size_t, GameObject*>::iterator it = copyMap.begin();

		//for (; it != objectFactory->GetGameObjectIDMap().end(); it++) {
		for (int x = 0; x < 6, it != copyMap.end(); x++, it++) {
			//std::cout << it->second->GetName() << std::endl;
			if (it->second->GetType() == "Button") {
				if (it->second->GetName() == "Exit") {
					//std::cout << it->second->GetName();
					Collider* collider = GET_COMPONENT(it->second, Collider, ComponentType::COLLIDER);

					OpenGLObject::FrameBufferMouseCoords(windowNew, &convertedMousePos.first, &convertedMousePos.second, OpenGLObject::cameraObject);
					std::cout << "Current Coords: " << convertedMousePos.first << ", " << convertedMousePos.second << '\t';
					std::cout << collider->boundingbox->min.x << ", " << collider->boundingbox->min.y <<'\t' << collider->boundingbox->max.x << ", " << collider->boundingbox->max.y << '\n';

					if (CollisionMouseRect(*(collider->boundingbox), convertedMousePos.first, convertedMousePos.second)) {
						std::cout << "YESSS";
					}
				}
			}

		}
	}
	(void)dt;
}


/**************************************************************************
* @brief This destructor handles shutdown of the UI system
* @return No return
*************************************************************************/
UIManager::~UIManager() {

}


/**************************************************************************
* @brief This function maps window coordinates of the entire window into the render window
* @param inputCoords - Input coordinates to map to
* @param targetWindowOrigin - The Origin point offset of the target window in respect to the top left corner of the main window
* @param wop - The window origin point of the taget window
* @param targetWindowSize - The dimensions of the target window
* @return Returns a pair of ints representing the mapped position
*************************************************************************/
//std::pair<int, int> UIManager::ConvertCoordsWindowToWindow(
//	std::pair<int, int> inputCoords,
//	std::pair<int, int> sourceWindowSize,
//	std::pair<int, int> targetWindowOrigin,
//	std::pair<int, int> targetWindowSize,
//	UIManager::WindowOriginPoint targetWindowOP) {
//	
//	std::pair<int, int> result;
//
//	// Get offset of target window
//	std::pair<int, int> windowOffset;
//	windowOffset.first = targetWindowOrigin.first;
//	windowOffset.second = targetWindowOrigin.second;
//
//	// For target window origin at center
//	if (targetWindowOP == UIManager::WindowOriginPoint::CENTER) {
//		//windowOffset.first -= targetWindowSize.first / 2;
//		//windowOffset.second -= targetWindowSize.second / 2;
//	}
//	// Map input coords
//	result.first = inputCoords.first - windowOffset.first;
//	result.second = inputCoords.second - windowOffset.second;
//	// Scale input coords
//	result.first = (result.first * targetWindowSize.first) / sourceWindowSize.first;
//	result.second = (result.second * targetWindowSize.second) / sourceWindowSize.second;
//	return result;
//
//}
