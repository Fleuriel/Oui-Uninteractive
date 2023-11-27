/**************************************************************************
 * @file Scene1.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-11-2023
 * @brief This file contains the declaration of the Scene1 Class,
 *		  which is a subset of IComponent to be contained in GameObject.
 *		  It holds  functions to enable scene1 transition in the engine.
 *************************************************************************/

#pragma once
#include "IScene.h"
#include <iostream>
#include "ObjectFactory.h"
#include "Transform.h"
#include "SceneManager.h"
#include <Input.h>
#include "Filepaths.h"
#ifndef SCENE1_H
#define SCENE1_H
class Scene1 : public IScene {
public:

	/**************************************************************************
	* @brief Constructor of Scene1
	*************************************************************************/
	Scene1(unsigned int id);

	/**************************************************************************
	* @brief Load for Scene1 
	* @return void
	*************************************************************************/
	virtual void Load();

	/**************************************************************************
	* @brief Initialize for Scene1
	* @return void
	*************************************************************************/
	virtual void Initialize();

	/**************************************************************************
	* @brief Updates Scene 1
	* @param dt deltaTime for every single update.
	* @return void
	*************************************************************************/
	virtual void Update(float dt) ;

	/**************************************************************************
	* @brief Draws Scene1
	* @return void
	*************************************************************************/
	virtual void Draw() ;

	/**************************************************************************
	* @brief Free For Scene1
	* @return void
	*************************************************************************/
	virtual void Free() ;

	/**************************************************************************
	* @brief Unloads Scene1
	* @return void
	*************************************************************************/
	virtual void Unload() ;

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~Scene1();
};
#endif 