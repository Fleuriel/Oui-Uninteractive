/**************************************************************************
 * @file UI.h
 * @author LOW Wang Chun, Mark - 100%
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-10-2023
 * @brief This source file contains the decleration of the UI class used to and handle UI functionality within the game
 *************************************************************************/
#ifndef UI_H
#define UI_H

#include "OpenGLObjects.h"
#include "ObjectFactory.h"
#include "ISystem.h"
#include "Collision.h"
#include "Editor.h"
#include "Input.h"
#include "SceneManager.h"
#include <array>
#include <iostream>

#define GET_COMPONENT(GameObject, Component, ComponentType) (GameObject->GetComponentType<Component>(ComponentType))

class UIManager : public ISystem {
public:
	UIManager();
	void Initialize();
	virtual void Update(float dt);
	bool test;
	~UIManager();


	enum class WindowOriginPoint {
		TOP_LEFT = 0,
		BOTTOM_LEFT,
		CENTER
	};

	std::pair<int, int> ConvertCoordsWindowToWindow(
		std::pair<int, int> inputCoords, 
		std::pair<int, int> sourceWindowSize,
		std::pair<int, int> targetWindowOrigin,
		std::pair<int, int> targetWindowSize, 
		WindowOriginPoint targetWindowOP);

private:

};
extern UIManager* uiManager;

#endif
