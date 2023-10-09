#pragma once
#include "IComponent.h"
class LogicComponent : public IComponent {
public:
	unsigned int logicIndex;

public:
	void Initialize();
	void Serialize(rapidjson::Value::ConstMemberIterator& itr) ;
	LogicComponent* Clone() const;
	~LogicComponent() {};
	void SetLogicIndex(const unsigned int & newLogicIndex);
	unsigned int GetLogicIndex();
};