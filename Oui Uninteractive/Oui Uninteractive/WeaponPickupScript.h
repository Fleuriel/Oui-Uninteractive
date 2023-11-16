#pragma once
#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"

class WeaponPickupScript : public IScript {
public:
	WeaponPickupScript(std::string newName) : IScript(newName) {

	};
	void Initialize() {
		logicSystem->AddLogicScript(this);
	};

	void Update(size_t gameObjectID) {

	};

	void End() {}
	~WeaponPickupScript() {}
};