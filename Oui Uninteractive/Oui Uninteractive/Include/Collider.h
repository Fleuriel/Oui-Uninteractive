#pragma once
#include "IComponent.h"
#include "Vector2D.h"
#include "Transform.h"
class Collider : public IComponent {
public:
	class AABB {
	public:
		//Extents of the Axis Aligned Bounding Box
		Vec2 min, max, x, y, center;
		Transform* tx;
		/**************************************************************************
		* @brief Default constructor for AABB
		*************************************************************************/
		AABB();
	};
	void Initialize();
	void Serialize(rapidjson::Value::ConstMemberIterator& itr);
	Collider* Clone() const;
	Collider();
	~Collider();
	//Pointer to Bounding Box object
	AABB* boundingbox;
};