#include "Logic.h"

LogicSystem* logicSystem = nullptr;
void LogicSystem::Initialize() {
	if (logicSystem != nullptr) {
		//instantiate physics system
		return;
	}
	else {
		logicSystem = this;
	}
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