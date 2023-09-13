#pragma once

class IComponent;

template <typename T>
class ComponentFactory {
private:

public:
	size_t type;

	ComponentFactory(size_t componentType) : type{componentType} {}
	~ComponentFactory() {}

	IComponent* CreateComponent() { return new T() };
};
