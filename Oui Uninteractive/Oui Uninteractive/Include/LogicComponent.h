#pragma once
#include "IComponent.h"
#include <set>
class LogicComponent : public IComponent {
public:
	unsigned int logicIndex;
	std::set<unsigned int> scriptIndexSet;
public:
	void Initialize();
	void Serialize(rapidjson::Value::ConstMemberIterator& itr) ;
	LogicComponent* Clone() const;
	~LogicComponent() ;
	void SetLogicIndex(const unsigned int & newLogicIndex);
	unsigned int GetLogicIndex();

	/*----------TESTING MESSAGING SYSTEM----------*/
	virtual void RegisterObserver(IObserver* observer);
	virtual void UnregisterObserver(IObserver* observer);
	virtual void NotifyObservers(IMessage* message);
	/*----------TESTING MESSAGING SYSTEM----------*/
};	