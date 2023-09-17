#include "Vector2D.h"
#include "IComponent.h"
class Transform : public IComponent {
public:
	Transform();
	Vec2 position;
	float scale;
	float rotation;
	//void Serialize(ISerializer& str);
};