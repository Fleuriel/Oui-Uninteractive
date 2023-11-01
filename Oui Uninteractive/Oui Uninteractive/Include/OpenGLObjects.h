/**************************************************************************
 * @file OpenGLObjects.h
 * @author 	TAN Angus Yit Hoe
 * @co-author CHEAH Tristan Tze Hong, HWANG Jing Rui, Austin, LOW Wang Chun, Mark, CHAN Aaron Jun Xiang, QUEK Cheng Kwang Emery
 * @par DP email: tan.a@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 29-09-2023
 * @brief 
 * This file contains the headers for OpenGLObject.cpp which
 * compute the logic behind the box model and encapsulates the
 * shader programs into a vector to store it, and allows for usage of them
 * for Translation, Scale, Rotation, and setting up textures.
 *************************************************************************/

#ifndef OPENGL_OBJECTS_H
#define OPENGL_OBJECTS_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/GL.h>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <OpenGLShaders.h>
#include <Vector2D.h>
#include <ISystem.h>
#include <AssetManager.h>
#include <GLFW/glfw3.h>

enum class SHADER_ORDER {
	MODEL = 0,
	FONT = 1,
	CAMERA = 2,

};


// External Texture Color
extern int importTexture, secondTexture, thirdTexture;

class OpenGLObject{
public:
	/**************************************************************************
	* @brief Constructor and Destructor
	**************************************************************************/
	// Default Constructor
	OpenGLObject(int id = 0) : 
		scaleModel(0.5, 0.5) , orientation(0.0, 0.0f), position(0, 0), 
		model_To_NDC_xform(glm::mat3(1.0f)), color(0.0f, 0.0f, 1.0f), interactable(true),
		angleDisplacment(0.0f), angleSpeed(0.0f), TagID(id)
	{};

	// Constructor for Particles
	OpenGLObject(glm::vec3 particlecolor) : 
		scaleModel(1, 1), orientation(0.0, 0.0f), position(0, 0), 
		model_To_NDC_xform(glm::mat3(1.0f)), color(particlecolor), interactable(true),
		angleDisplacment(0.0f), angleSpeed(0.0f), TagID(0){
		std::cout << "R : " << color.r << "\nG : " << color.g << "\nB : " << color.b << "\n";
	};
	
	~OpenGLObject() {};

	static bool renderBoundingBox;


	int TagID;						// Id for the Model to Texture

	glm::vec2 scaleModel;			// Scale for the Model
	float angleDisplacment;			// Angle of the Model (Start)
	float angleSpeed;				// Speed of the Model Displacement
	glm::vec2 orientation;			// Rotation
	glm::vec2 position;				// translation

	glm::mat3 model_To_NDC_xform;	// Model to NDC 
	glm::vec3 color;				// Set Object Color
	bool interactable;				// if the object is interactable?
	static GLuint mdl_ref, shd_ref; // Model and Shader Reference

	static GLuint VAO, VBO;			// Object VAO VBO
	
	// Frame Buffers
	static GLuint FBO;
	static GLuint RBO;				// rendering buffer object

	static GLuint FrameTexture;


	

	// encapsulates state required to render a geometrical model
	struct OpenGLModel {
		GLenum primitive_type;		// Primitive Type
		size_t primitive_cnt;		// Primitive Count
		GLuint vaoid;				// Vaoid of the Model
		GLsizei draw_cnt;			// Draw Count of the model
		size_t idx_elem_cnt;		// Index Element Count of the Model
		

		OpenGLModel() : primitive_type(0), primitive_cnt(0), vaoid(0), draw_cnt(0), idx_elem_cnt(0)  {}

		struct VAO_Object
		{
			glm::vec2 position;				// VAO position
			glm::vec3 color;				// VAO color
			glm::vec2 texture;				// VAO texture

			// constructor for VAO_Obj ...
			VAO_Object() : position(0.0, 0.0), color(0.0, 0.0, 0.0), texture(0, 0) {}

			// Member Functions:

			/**************************************************************************
			* @brief		set Texture Positon, Color
			*
			* @param  float x axis of texture
			* @param  float y axis of texture
			* @param  float r Red Color Value
			* @param  float g Green Color Value
			* @param  float b Blue Color Value
			*
			* @return void
			*************************************************************************/
			void setTextureValue(float, float, float, float, float);


			/**************************************************************************
			* @brief		set Texture Positon, Color
			*
			* @param  float s axis of texture
			* @param  float t axis of texture
			*
			* @return void
			*************************************************************************/
			void setTexture(float, float);
		};
	};




	// Camera Structure
	struct Camera2D {

		Camera2D() : up(0, 0), right(0,0), view_xform(0), CameraWindow_to_NDC_xform(0), World_to_NDC_xform(0),
 		aspectRatio (0){}

		OpenGLObject *Cam;

		GLfloat posX, posY;

		glm::vec2 up, right;
		glm::mat3 view_xform, CameraWindow_to_NDC_xform, World_to_NDC_xform;
		
		GLfloat height{ 1000 }; // Current Height of the depth i.e. Zoom
		GLfloat min_height{ 0 };
		GLfloat max_height{ 2000 };


		GLfloat aspectRatio;

		// 1 or -1.
		GLint heightChangeBoolean{ 1 };

		GLint heightChangeValue{ 5 };

		GLfloat linearSpeed{ 2.0f };



		void Init(GLFWwindow*, OpenGLObject* ptr);

		void Update(GLFWwindow*, int, int);

	};
	static glm::mat4 projection;
	static OpenGLObject cameraTranslator;
	static Camera2D cameraObject;



/**************************************************************************
	* @brief		Initialize OpenGLObject that does Model Creation for future
	*				Drawing Capabilities and Shader Emplacement.
	*
	* @WARNING _DEBUG debug draws a model of square.
	*
	* @param  none
	* @return void
	*************************************************************************/
	void Initialize(); 
	/**************************************************************************
	* @brief		Updates each OpenGLObject with Movement, Scale rotation.
	*				Option for rotation has been added.
	*
	* @param float  Acceleration of x-Axis
	* @param float  Acceleration of y-Axis
	* @param float  Scale on both X and Y axes. (Might need to change)
	* @param float  Angle Rotation Speed
	* @param bool   Boolean for Rotation Enable or Disable
	* @return void
	*************************************************************************/
	void Update(float newX, float newY, float scaleX, float scaleY, float newAngle, bool enRot);

	/**************************************************************************
	* @brief		Draws a Debug Collision Box (AABB)
	*
	* @param  Vector2D	Minimum Coordinates of AABB
	* @param  Vector2D  Maximum Coordinates of AABB
	*
	* @return void
	*************************************************************************/
	void DrawCollisionBox(Vector2D min, Vector2D max);
	/**************************************************************************
	* @brief		Draws the OpenGLObject.
	*
	* @param  none
	* @return void
	*************************************************************************/
	void Draw(int shaderNumber = 0) const;

	/**************************************************************************
	* @brief		Initialize the Shaders for Graphics Pipeline for Object to
	*				Render and/or Translate their objects.
	*
	* @param  float User Input X coordinate
	* @param  float User Input Y Coordinate
	* @param  float User Input Size X (Scale X Axis)
	* @param  float User Input Size Y (Scale Y Axis)
	* @param  float User Input Angle Displacement (Anti Clockwise)
	* @param  float User Input Angle Speed (Speed of rotation)
	*
	* @return void
	*************************************************************************/
	void InitObjects(float userInput_x = 0.0f, float userInput_y = 0.0f, float userInput_sizeX = 0.0f,
					float userInput_sizeY = 0.0f, float userInput_angleDisplacement = 0.0f,
					float userInput_angleSpeed = 0.0f);

	/**************************************************************************
	* @brief		 Cleanup the Object Creation.
	* @param  none
	* @return void
	*************************************************************************/
	static void Cleanup();


	/**************************************************************************
	* @brief		 Camera Update
	* @param  none
	* @return void
	*************************************************************************/
	void CameraUpdate(int, int);

	// 
	using VectorPairStrStr = std::vector <std::pair<std::string, std::string>>;
	// Initialize the shader programs to encapsulate the shader to 
	// allow drawing.
	static void init_shdrpgms_cont(VectorPairStrStr const& vpss);

	// < Models >
	// Square/Box Model
	static OpenGLModel Box_Model(glm::vec3);

	// < Texture >
	static int Setup_TextureObject(std::string filePath);

	// Create Container For OpenGLModel
	static std::vector<OpenGLModel> models;

	//Shaders
	static std::vector<OpenGLShader>shdrpgms;

	static void InitShaders();

	static void InitFont();
	//static void 
	static void FrameBufferMouseCoords(GLFWwindow*, double *x, double *y, Camera2D);

private:

};



// Vector for shdrpgms
extern std::vector<OpenGLShader> shdrpgms;

//extern OpenGLObject::Camera2D cameraObject;

#endif // OPENGL_OBJECTS_H