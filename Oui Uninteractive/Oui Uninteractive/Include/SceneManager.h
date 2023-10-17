#pragma once
#include "ISystem.h"
#include "IScene.h"
#include "Scene1.h"
#include <map>

#ifndef SCENEMANAGER_H
#define SCENEMANAGER
class SceneManager : public ISystem {
public: 
	std::map<size_t, IScene*> sceneMap;
	IScene* currScene;

	SceneManager();
	void Load();
	void Initialize();
	virtual void Update(float dt) override;
	~SceneManager();

	void InitScene();
};
extern SceneManager* sceneManager;

#endif