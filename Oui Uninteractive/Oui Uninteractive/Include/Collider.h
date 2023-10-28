#pragma once
#include "IComponent.h"
#include "Vector2D.h"
#include "Transform.h"


#ifndef COLLIDER_H
#define COLLIDER_H
class Collider;
class Collider : public IComponent {
public:
	class AABB {
	public:
		//Extents of the Axis Aligned Bounding Box
		Vec2 min, max, x, y, center;
		Transform* txPtr;
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
	Transform* tx;
	AABB* boundingbox;
	float contactTime;
	std::pair<int, int> implicitGridPos;
};
#endif