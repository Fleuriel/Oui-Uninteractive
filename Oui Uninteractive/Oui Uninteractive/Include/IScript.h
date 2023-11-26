#pragma once

#include <string>
class IScript {
public:
	IScript(std::string newName, bool gameplayFlag) {
		name = newName;
		isGameplay = gameplayFlag;
	};
	virtual void Initialize() {};
	virtual void Update(size_t) {};
	virtual void End() {};
	virtual ~IScript() {};
	std::string name;
	bool isGameplay;
};