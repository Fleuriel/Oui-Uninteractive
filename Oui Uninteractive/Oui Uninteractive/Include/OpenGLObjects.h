/**************************************************************************
 * @file OpenGLObjects.h
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
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


#define TRIANGLE "Triangle"
#define SQUARE   "Square"
#define CIRCLE   "Circle"

extern int importTexture, secondTexture, bgTexture;

class OpenGLObject
{
public:
	OpenGLObject(int id = 0) : 
		scaleModel(0.5, 0.5) , orientation(0.0, 0.0f), position(0, 0), 
		model_To_NDC_xform(glm::mat3(1.0f)), color(0.0f, 0.0f, 1.0f), interactable(true),
		angleDisplacment(0.0f), angleSpeed(0.0f), TagID(id)
	{

	};

	OpenGLObject(glm::vec3 particlecolor) : 
		scaleModel(1, 1), orientation(0.0, 0.0f), position(0, 0), 
		model_To_NDC_xform(glm::mat3(1.0f)), color(particlecolor), interactable(true),
		angleDisplacment(0.0f), angleSpeed(0.0f), TagID(0){
		std::cout << "R : " << color.r << "\nG : " << color.g << "\nB : " << color.b << "\n";
	};
	
	~OpenGLObject() {};

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
	//GLuint texture;					// integer for texture (stb returns integer).


	static GLuint VAO, VBO;			// Object VAO VBO


//	void AddModel(int modelID, int TextureID,);


	// encapsulates state required to render a geometrical model
	struct OpenGLModel {
		GLenum primitive_type;
		size_t primitive_cnt;
		GLuint vaoid;
		GLuint draw_cnt;

		size_t idx_elem_cnt;
		GLuint model_cnt;			// added to check model count
		GLuint texture;
		
		int ModelID;

		std::vector <glm::vec2> Position_Vertex;

		OpenGLModel() : primitive_type(0), primitive_cnt(0), vaoid(0), draw_cnt(0), model_cnt(0), ModelID(0) {}


		struct VAO_Object
		{
			glm::vec2 position;				// VAO position
			glm::vec3 color;					// VAO color
			glm::vec2 texture;				// VAO texture

			// ctor for VAO_Obj ...
			VAO_Object() : position(0.0, 0.0), color(0.0, 0.0, 0.0), texture(0, 0) {}

			// Member Functions:

			// Set Values for VAO (Position, Color)
			void setTextureValue(float, float, float, float, float);

			// Set Texture for VAO (texture)
			void setTexture(float, float);

		};
		void draw() const;
		void setup_TextureVAO();
	};




	//std::map<std::string, OpenGLModel>::iterator mdl_ref;
	//std::map<std::string, OpenGLShader>::iterator shd_ref;

	// set up initial state
	void Init(); 

	void Update(float xSpeed = 0.0f, float ySpeed = 0.0f, float scaleX = 100.0f, float scaleY = 100.0f, float aSpeed = 10.0f, bool enRot = false);
	//static void OpenGLShadersInitialization();

	void Draw() const;

	void InitObjects(float userInput_x, float userInput_y, float userInput_sizeX,
					float userInput_sizeY, float userInput_angleDisplacement,
					float userInput_angleSpeed);
	static void Cleanup();
//	static void Setup_Quad_VAO();
	static void init_scenes(std::string);
	static void Insert_Shader_Program(std::string shdr_pgm_name, std::string vtx_shdr_name, std::string frg_shdr_name);

	static std::vector<OpenGLModel> models;

	//Shaders
	static std::vector<OpenGLShader>shdrpgms;
	using VectorPairStrStr = std::vector <std::pair<std::string, std::string>>;
	static GLuint ShaderProgram;
	//static std::map<std::string, OpenGLShader> shdrpgms;


	static std::vector<GLuint> textures;


	static void init_shdrpgms_cont(VectorPairStrStr const& vpss);

	// Models

	static OpenGLModel Box_Model(int ID, glm::vec3, int);


	// Texture
	static int Setup_TextureObject(std::string filePath);
	//void setTextureValue(float, float, float, float, float);
	//void setTexture(float, float);


	// Data for Square and Triangles
	static std::vector<glm::vec2> square;
	static std::vector<glm::vec2> triangle;
	static std::vector<std::string> mesh_Directory;
	
	static GLuint textureID;

	// Store Models inside:
	static std::map<std::string, OpenGLModel> Model_Storage;
	static std::map<std::string, OpenGLObject> Object_Storage;



private:

};

#endif // OPENGL_OBJECTS_H