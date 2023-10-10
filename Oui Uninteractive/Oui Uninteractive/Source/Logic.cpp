#include "Logic.h"
#include "ComponentFactory.h"
#include <iostream>

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
	for (auto& iter : logicComponentMap) {
		scriptVec[iter.second->GetLogicIndex()]->Update(iter.second->GetOwner()->GetGameObjectID());
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