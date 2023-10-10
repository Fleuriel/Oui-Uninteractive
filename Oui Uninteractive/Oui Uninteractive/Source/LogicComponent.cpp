#include "LogicComponent.h"
#include "Logic.h"
#include <algorithm>
//Logic Components Index denotes which Script u want it to run
LogicComponent::~LogicComponent() {
	logicSystem->logicComponentMap.erase(GetOwner()->GetGameObjectID());
}
void LogicComponent::Initialize() {
	//logicSystem->logicComponentVec.push_back(this);
	logicSystem->logicComponentMap.insert(std::pair<size_t, LogicComponent*>(GetOwner()->GetGameObjectID(), this));
	logicIndex = 0;
}
void LogicComponent::SetLogicIndex(const unsigned int& newLogicIndex) {
	logicIndex = newLogicIndex;
}

void LogicComponent::Serialize(rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };
	logicIndex = components["LogicIndex"].GetFloat();
}

LogicComponent* LogicComponent::Clone() const {
	LogicComponent* newLogic = new LogicComponent();
	newLogic->logicIndex = logicIndex;

	return newLogic;
}
//which script do u want to run (can make it a range in the future)
unsigned int LogicComponent::GetLogicIndex() {
	return logicIndex;
}