#pragma once
#include "IComponent.h"
#include <set>
class LogicComponent : public IComponent {
public:

	std::set<unsigned int> scriptIndexSet;
public:
	void Initialize();
	void Serialize(rapidjson::Value::ConstMemberIterator& itr) ;
	LogicComponent* Clone() const;
	~LogicComponent() ;
	
};	