#pragma once
class IScript {
public:
	virtual void Initialize() {};
	virtual void Update(size_t gameObjectID) {};
	virtual void End() {};
	virtual ~IScript() {};
};