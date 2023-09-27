#include "Vector2D.h"
#include "IComponent.h"
#include "GameObject.h"
#include "OpenGLObjects.h"

class Transform : public IComponent {
public:
	/**************************************************************************
	* @brief Default constructor for Transform component
	*************************************************************************/
	Transform();
	/**************************************************************************
	* @brief Destructor for Transform component
	*************************************************************************/
	~Transform();
	/**************************************************************************
	* @brief Initialize function for the Transform Component
	* @return void
	*************************************************************************/
	virtual void Initialize();
	/**************************************************************************
	* @brief Initialize this instance of the Transform component via file
	* @param filePath - file path to read from
	* @param itr - iterator through json object
	* @return void
	*************************************************************************/
	void Serialize(const std::string& filePath, rapidjson::Value::ConstMemberIterator& itr);
	/**************************************************************************
	* @brief Function to Clone a Transform Component
	* @return Transform* - the cloned Transform
	*************************************************************************/
	virtual Transform* Clone() const;
	//Member Variables
	Vec2 position;
	float scale;
	float rotation;
	OpenGLObject* shape;
};