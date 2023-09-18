
#include "Physics.h"

PhysicsBody::PhysicsBody() {
	position = Vec2(0, 0);
	velocity = Vec2(0, 0);
	acceleration = Vec2(0, 0);
	isStatic = false;
}
void PhysicsBody::Initialize() {
	//Transform
	//assign pos to transform
	if (GetOwner()->Has(ComponentType::Transform) != -1) {
		txPtr = GetOwner()->GetComponentType<Transform>(ComponentType::Transform);
		position = txPtr->position;
	}
	
	

	physicsSys->bodyList.push_back(this);

}
void PhysicsBody::Serialize(std::string filePath, JsonSerializer serializer) {
	rapidjson::Document objDoc;

	// Read from JSON file
	if (serializer.ReadJSONFile(filePath, objDoc)) {
		//body.someVar = objDoc["body"]["someVar"].GetString();
		/*position = objDoc["PhysicsBody"]["position"].GetString();
		velocity = objDoc["PhysicsBody"]["velocity"].GetString();
		accumulatedForce = objDoc["PhysicsBody"]["accumulatedForce"].GetString();
		prevPosition = objDoc["PhysicsBody"]["prevPosition"].GetString();
		acceleration = objDoc["PhysicsBody"]["acceleration"].GetString();*/
		
		position.x = objDoc[]

	}

}