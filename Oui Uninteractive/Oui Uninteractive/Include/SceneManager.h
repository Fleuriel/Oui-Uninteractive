/**************************************************************************
 * @file SceneManager.h
 * @author CHEAH Tristan Tze Hong - 100%
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 17-10-2023
 * @brief This file contains the declaration of the SceneManager class.
 *************************************************************************/

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

	SceneManager();
	void Load();
	void Initialize();
	virtual void Update(float dt) override;
	void Draw();
	void Free();
	void Unload();
	~SceneManager();

	void InitScene();
};
extern SceneManager* sceneManager;

#endif