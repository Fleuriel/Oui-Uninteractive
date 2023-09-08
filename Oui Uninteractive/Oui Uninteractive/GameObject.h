#pragma once

#include "IComponent.h"
#include <vector>

class GameObject {
private:
	std::vector<IComponent*> componentList;
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual ~GameObject() {};

	void AddComponent(IComponent* c) { componentList.push_back(c); }
	void RemoveComponent(IComponent* c) {}
	bool Has(IComponent* c) {}
};
