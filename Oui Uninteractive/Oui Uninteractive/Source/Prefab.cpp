/**************************************************************************
 * @file Prefab.cpp
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 01-11-2023
 * @brief This file contains the definition of the Prefab class.
 *************************************************************************/
#include "Prefab.h"

Prefab::Prefab(const std::string& name, const std::string& type) {
	prefabName = name;
	prefabType = type;
}

Prefab::~Prefab() {
	for (int i{}; i < prefabComponentList.size(); ++i)
		delete prefabComponentList[i];
}

void Prefab::AddComponent(IComponent* c, ComponentType t) {
	c->componentType = t;
	prefabComponentList.push_back(c);
}

void Prefab::RemoveComponent(IComponent* c) {
	for (size_t i{}; i < prefabComponentList.size(); ++i) {
		if (prefabComponentList[i] == c) {
			prefabComponentList.erase(prefabComponentList.begin() + i);
			return;
		}
	}
}

int Prefab::Has(ComponentType typeID) {
	for (int i{}; i < prefabComponentList.size(); ++i) {
		if (prefabComponentList[i]->componentType == typeID) {
			return i;
		}
	}
	return -1;
}

std::string Prefab::GetName() {
	return prefabName;
}

std::string Prefab::GetType() {
	return prefabType;
}

std::vector<IComponent*> Prefab::GetprefabComponentList() {
	return prefabComponentList;
}

IComponent* Prefab::GetComponent(ComponentType typeID) {
	int index = Has(typeID);
	if (index >= 0) {
		return prefabComponentList.at(index);
	}
	return nullptr;
}
