#pragma once
#include "IComponent.h"
class LogicComponent : public IComponent {
protected:
	unsigned int logicIndex;

public:
	virtual void Initialize();
	void SetLogicIndex(const unsigned int & newLogicIndex);
	unsigned int GetLogicIndex();
};