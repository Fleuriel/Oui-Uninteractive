#include "LogicComponent.h"
#include "Logic.h"
#include <algorithm>
//Logic Components Index denotes which Script u want it to run
LogicComponent::~LogicComponent() {
	if (GetOwner() != nullptr) {
		logicSystem->logicComponentMap.erase(GetOwner()->GetGameObjectID());
	}
}
void LogicComponent::Initialize() {
	//logicSystem->logicComponentVec.push_back(this);
	logicSystem->logicComponentMap.insert(std::pair<size_t, LogicComponent*>(GetOwner()->GetGameObjectID(), this));
	
}

void LogicComponent::Serialize(rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };
	
	for (rapidjson::Value::ConstMemberIterator iter = components.MemberBegin(); iter != components.MemberEnd(); ++iter) {
		printf("%s\t", iter->name.GetString());
		for (auto& scriptID : iter->value.GetArray()) {
			switch (scriptID.GetInt()) {
			case 0:
				scriptIndexSet.insert(LOGIC_ENUM::TEST_SCRIPT1);
				break;
			case 1:
				scriptIndexSet.insert(LOGIC_ENUM::PLAYER_MOVEMENT);
				break;
			case 2:
				scriptIndexSet.insert(LOGIC_ENUM::ENEMY_FSM);
				break;
			case 3:
				scriptIndexSet.insert(LOGIC_ENUM::PLAYER_ATTACK);
				break;
			default:
				scriptIndexSet.insert(LOGIC_ENUM::TEST_SCRIPT1);
			}
		}
	}
}

LogicComponent* LogicComponent::Clone() const {
	LogicComponent* newLogic = new LogicComponent();
	
	newLogic->scriptIndexSet = scriptIndexSet;

	return newLogic;
}

