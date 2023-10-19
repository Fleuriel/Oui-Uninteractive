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
	virtual void Load();
	virtual void Initialize();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Free();
	virtual void Unload();

	~Scene2();
};
#endif 