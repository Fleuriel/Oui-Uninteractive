#pragma once
class IScript {
public:
	virtual void Initialize() {};
	virtual void Update(size_t) {};
	virtual void End() {};
	virtual ~IScript() {};
};