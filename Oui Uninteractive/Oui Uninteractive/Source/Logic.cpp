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
	ComponentFactory<LogicComponent>* testPtr = new ComponentFactory<LogicComponent>(ComponentType::LOGICCOMPONENT);
	objectFactory->AddComponentFactory(ComponentType::LOGICCOMPONENT, testPtr);
}

void LogicSystem::Update(float dt) {
	for (auto& iter : logicComponentMap) {
		for (unsigned int index : iter.second->scriptIndexSet) {
			scriptVec[index]->Update(iter.second->GetOwner()->GetGameObjectID());
		}
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