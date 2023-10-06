#include "Logic.h"
#include "ComponentFactory.h"

LogicSystem* logicSystem = nullptr;
LogicSystem::LogicSystem() {
	if (logicSystem != nullptr) {
		//instantiate physics system
		return;
	}
	else {
		logicSystem = this;
	}
}
void LogicSystem::Initialize() {
	ComponentFactory<LogicComponent>* testPtr = new ComponentFactory<LogicComponent>(ComponentType::LOGIC_COMPONENT);
	objectFactory->AddComponentFactory(ComponentType::LOGIC_COMPONENT, testPtr);
}

void LogicSystem::Update(float dt) {
	for (auto& iter : logicComponentVec) {
		scriptVec[iter->GetLogicIndex()]->Update(dt);
	}
}
void LogicSystem::AddLogicScript(IScript* newScript) {
	scriptVec.push_back(newScript);
}
LogicSystem::~LogicSystem() {
	for (int i = 0; i < scriptVec.size(); i++) {
		delete scriptVec[i];
	}
}