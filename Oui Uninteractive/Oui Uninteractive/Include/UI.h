/**************************************************************************
 * @file UI.h
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-10-2023
 * @brief This source file contains the decleration of the UI class used to and handle UI functionality within the game
 *************************************************************************/
#ifndef UI_H
#define UI_H

#include "ObjectFactory.h"
#include "ISystem.h"
#include "Collision.h"
#include "Editor.h"
#include <iostream>

#define GET_COMPONENT(GameObject, Component, ComponentType) (GameObject->GetComponentType<Component>(ComponentType))

class UIManager : public ISystem {
public:
	UIManager();
	void Initialize();
	virtual void Update(float dt);
	bool test;
	~UIManager();

private:

};
extern UIManager* uiManager;

#endif
