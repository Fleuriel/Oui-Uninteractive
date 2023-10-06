#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"
class TestScript : public IScript {
	void Initialize() {
		logicSystem->AddLogicScript(this);
	};

	void Update(size_t gameObjectID) {
		Transform* tx = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM);
		PhysicsBody* physBod = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
		if (tx != nullptr && physBod != nullptr) {
			physicsSys->MoveLeft(gameObjectID);
		}
	};

	void End() {};
};