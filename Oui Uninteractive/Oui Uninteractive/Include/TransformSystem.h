#pragma once
#include "ISystem.h"
class TransformSystem : public ISystem {
	void Initialize();
	void Update(float dt);
	~TransformSystem();
};