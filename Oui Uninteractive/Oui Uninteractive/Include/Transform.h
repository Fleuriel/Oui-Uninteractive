#include "Vector2D.h"
#include "IComponent.h"
#include "GameObject.h"

class Transform : public IComponent {
public:
	Transform();
	Vec2 position;
	float scale;
	float rotation;
	void Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr);
};