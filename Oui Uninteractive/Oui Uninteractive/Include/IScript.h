#pragma once
class IScript {
public:
	IScript(std::string newName) {
		name = newName;
	};
	virtual void Initialize() {};
	virtual void Update(size_t) {};
	virtual void End() {};
	virtual ~IScript() {};
	std::string name;
};