#include "IScript.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "Logic.h"
class TestScript : public IScript {
public:
	void Initialize() {
		logicSystem->AddLogicScript(this);
	};

	void Update(size_t gameObjectID) {
		GameObject* gObj = objectFactory->GetGameObjectByID(gameObjectID);
		Transform* tx = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM);
		PhysicsBody* physBod = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY);
		if (tx != nullptr && physBod != nullptr) {
			physicsSys->SetVelocity(physBod->speed * Vec2(physBod->direction.x, physBod->direction.y), gameObjectID);
		}
	};

	void End() {};
};