#pragma once
#include "IScene.h";
class Scene1 : public IScene {
	virtual void Load();
	virtual void Initialize();
	virtual void Update() ;
	virtual void Draw() ;
	virtual void Free() ;
	virtual void Unload() ;
};