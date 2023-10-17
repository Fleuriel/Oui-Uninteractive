#pragma once
#include "ISystem.h"
class SceneManager : public ISystem {
	SceneManager();
	void Initialize();
	virtual void Update(float dt) override;
	~SceneManager();
};
extern SceneManager* sceneManager;