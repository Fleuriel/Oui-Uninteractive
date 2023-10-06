#include "LogicComponent.h"
#include "Logic.h"

//Logic Components Index denotes which Script u want it to run
void LogicComponent::Initialize() {
	logicSystem->logicComponentVec.push_back(this);
	logicIndex = logicSystem->logicComponentVec.size() - 1;
}
void LogicComponent::SetLogicIndex(const unsigned int& newLogicIndex) {
	logicIndex = newLogicIndex;
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