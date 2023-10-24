#pragma once
#include "ISystem.h"
#include "Transform.h"
#include "ComponentFactory.h"
#include "ObjectFactory.h"
#include "ColliderSystem.h"
class TransformSystem : public ISystem {
	void Initialize();
	void Update(float dt);
	~TransformSystem();
};