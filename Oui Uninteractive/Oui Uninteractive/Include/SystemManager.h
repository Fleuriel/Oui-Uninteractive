#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <vector>
#include "ISystem.h"

class SystemManager {
public:
	SystemManager();
	~SystemManager();
	void Initialize();
	void AddSystem(ISystem* system);
	void DestroySystem();
	void UpdateSystems(float dt);

private:
	std::vector<ISystem*> Systems;
};

extern SystemManager* sysManager;

#endif
