#pragma once
#include "IScene.h"
#include <iostream>
#include "ObjectFactory.h"
#include "Transform.h"
#ifndef SCENE1_H
#define SCENE1_H
class Scene1 : public IScene {
public:
	Scene1(unsigned int id);
	virtual void Load();
	virtual void Initialize();
	virtual void Update(float dt) ;
	virtual void Draw() ;
	virtual void Free() ;
	virtual void Unload() ;

	~Scene1();
};
#endif 