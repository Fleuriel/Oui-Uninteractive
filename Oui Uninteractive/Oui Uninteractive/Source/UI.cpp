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

	// 1. Loop through game obj list
	// 2. if its type is button
	// 3. if its name is exit
	// 4. if its clicked
	// 5. Quit
	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	std::map<size_t, GameObject*>::iterator it = copyMap.begin();
	//for (; it != objectFactory->GetGameObjectIDMap().end(); it++) {
	for (int x = 0; x < 6; x++, it++) {
			//std::cout << it->second->GetName() << std::endl;
			if (it->second->GetType() == "Button") {
				if (it->second->GetName() == "Exit") {
					//std::cout << it->second->GetName();
					Collider* collider = GET_COMPONENT(it->second, Collider, ComponentType::COLLIDER);
					if (CollisionMouseRect(*(collider->boundingbox))) {
						std::cout << "YESSS";
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