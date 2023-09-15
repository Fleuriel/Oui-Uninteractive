#include "SystemManager.h"
SystemManager* sysManager;
SystemManager::SystemManager() {
	sysManager = this;
}
SystemManager::~SystemManager() {

}
void SystemManager::Initialize() {
	for (int i = 0; i < Systems.size(); i++) {
		Systems[i]->Initialize();
	}
}
void SystemManager::UpdateSystems(float dt) {
	for (int i = 0; i < Systems.size(); i++) {
		Systems[i]->Update(dt);
	}
}
void SystemManager::AddSystem(ISystem* system) {
	Systems.push_back(system);

}
void SystemManager::DestroySystem() {
	for (int i = 0; i < Systems.size(); i++) {
		delete Systems[Systems.size() - i - 1];
	}
}