#pragma once
#include "ISystem.h"
#include "IScript.h"
#include "LogicComponent.h"
#include "ObjectFactory.h"
#include <vector>
class LogicSystem : public ISystem {
public:
	LogicSystem();
	void Initialize();
	void Update(float dt);
	void AddLogicScript(IScript* newScript);
	~LogicSystem();

	//insert script container
	std::vector<IScript*> scriptVec;
	//insert logic component container
	std::vector<LogicComponent*> logicComponentVec;
};
extern LogicSystem* logicSystem;