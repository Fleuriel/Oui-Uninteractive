/**************************************************************************
 * @file SceneManager.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 08-09-2023
 * @brief This file contains the declaration of the SceneManager to manage
 *		  Scenes.
 *************************************************************************/

#pragma once
#include "ISystem.h"
#include "IScene.h"
#include "Scene1.h"
#include "Scene2.h"
#include <map>

#ifndef SCENEMANAGER_H
#define SCENEMANAGER
// Game State List Enumeration
enum GameStateList
{
	STATE_GRAPHICS_TEST = 0,
	STATE_LEVEL_TEST,
	STATE_GAME_TEST,
	STATE_RESTART,
	STATE_QUIT
};
class SceneManager : public ISystem {
public: 
	unsigned int currSceneID;
	unsigned int nextSceneID;
	unsigned int prevSceneID;

	std::map<size_t, IScene*> sceneMap;
	IScene* currScene;


	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	SceneManager();

	/**************************************************************************
	* @brief Loads Scene Manager
	* @return void
	*************************************************************************/
	void Load();

	/**************************************************************************
	* @brief Initializes Scene Manager
	* @return void
	*************************************************************************/
	void Initialize();

	/**************************************************************************
	* @brief Updates Scene Manager
	* @param float dt deltaTime to update per frame
	* @return void
	*************************************************************************/
	virtual void Update(float dt) override;

	/**************************************************************************
	* @brief Draws Scene Manager
	* @return void
	*************************************************************************/
	void Draw();

	/**************************************************************************
	* @brief Frees Scene Manager
	* @return void
	*************************************************************************/
	void Free();

	/**************************************************************************
	* @brief Unloads Scene Manager
	* @return void
	*************************************************************************/
	void Unload();

	/**************************************************************************
	* @brief Desturcor
	*************************************************************************/
	~SceneManager();

	/**************************************************************************
	* @brief Initializes Scene 
	* @return void
	*************************************************************************/
	void InitScene();
};
extern SceneManager* sceneManager;

#endif