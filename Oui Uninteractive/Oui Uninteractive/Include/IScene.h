#pragma once
class IScene {
public:
	unsigned int sceneID;
	IScene(unsigned int id) {
		sceneID = id;
	};
	virtual void Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void Free() = 0;
	virtual void Unload() = 0;

	virtual ~IScene() {};
};