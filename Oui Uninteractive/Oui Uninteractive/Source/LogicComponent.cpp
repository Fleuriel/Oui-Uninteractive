#include "LogicComponent.h"
#include "Logic.h"
#include <algorithm>

/**************************************************************************
* @brief Destructor for Logic component
*************************************************************************/
LogicComponent::~LogicComponent() {
	if (GetOwner() != nullptr) {
		logicSystem->logicComponentMap.erase(GetOwner()->GetGameObjectID());
	}
}
/**************************************************************************
* @brief Initialize function for Logic Component
* @return void
*************************************************************************/
void LogicComponent::Initialize() {
	logicSystem->logicComponentMap.insert(std::pair<size_t, LogicComponent*>(GetOwner()->GetGameObjectID(), this));
	
}
/**************************************************************************
* @brief Serialize function for logic component
* @param itr - iterator through json object
* @return void
*************************************************************************/
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
/**************************************************************************
* @brief Function to Clone a Logic Component Component
* @return LogicComponent* - the cloned Logic Component
*************************************************************************/
LogicComponent* LogicComponent::Clone() const {
	LogicComponent* newLogic = new LogicComponent();
	
	newLogic->scriptIndexSet = scriptIndexSet;

	return newLogic;
}

