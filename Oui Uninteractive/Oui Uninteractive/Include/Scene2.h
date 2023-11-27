/**************************************************************************
 * @file Scene2.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-11-2023
 * @brief This file contains the declaration of the Scene2 Class,
 *		  which is a subset of IComponent to be contained in GameObject.
*		  It holds  functions to enable scene2 transition in the engine.
 *************************************************************************/

#pragma once
#include "IScene.h"
#include <iostream>
#include "ObjectFactory.h"
#include "SceneManager.h"
#include "Transform.h"
#ifndef SCENE2_H
#define SCENE2_H
class Scene2 : public IScene {
public:
	Scene2(unsigned int id);

	/**************************************************************************
	* @brief Loads Scene2
	* @return void
	*************************************************************************/
	virtual void Load();

	/**************************************************************************
	* @brief Initializes Scene2
	* @return void
	*************************************************************************/
	virtual void Initialize();

	/**************************************************************************
	* @brief Updates Scene2
	* @param dt		deltatime for per frame update
	* @return void
	*************************************************************************/
	virtual void Update(float dt);

	/**************************************************************************
	* @brief Draw Scene2
	* @return void
	*************************************************************************/
	virtual void Draw();

	/**************************************************************************
	* @brief Frees Scene2
	* @return void
	*************************************************************************/
	virtual void Free();

	/**************************************************************************
	* @brief Unloads Scene2
	* @return void
	*************************************************************************/
	virtual void Unload();

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~Scene2();
};
#endif 