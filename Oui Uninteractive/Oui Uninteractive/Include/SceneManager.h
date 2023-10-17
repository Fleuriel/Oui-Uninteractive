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