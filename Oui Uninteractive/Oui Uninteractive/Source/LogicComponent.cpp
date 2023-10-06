#include "LogicComponent.h"
#include "Logic.h"
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
unsigned int LogicComponent::GetLogicIndex() {
	return logicIndex;
}