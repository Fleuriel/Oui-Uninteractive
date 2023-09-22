#include "Vector2D.h"
#include "IComponent.h"
#include "GameObject.h"
#include "OpenGLObjects.h"


class Transform : public IComponent {
public:
	Transform();
	~Transform();
	Vec2 position;
	float scale;
	float rotation;
	void Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr);
	OpenGLObject* graphics;
};