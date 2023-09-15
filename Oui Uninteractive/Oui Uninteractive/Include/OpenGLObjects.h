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


class OpenGLObject
{
public:
	OpenGLObject() : scaling(0.5, 0.5), orientation(0.0, 0.0f), position(0, 0), model_To_NDC_xform(glm::mat3(1.0f)), color(1.0, 1.0, 1.0f){};


	glm::vec2 scaling; // scaling
	glm::vec2 orientation; 
	glm::vec2 position; // translation
	glm::mat3 model_To_NDC_xform;
	glm::vec3 color;



	static GLuint VAO, VBO;

	// encapsulates state required to render a geometrical model
	struct OpenGLModel {
		GLenum primitive_type;
		GLuint primitive_cnt;
		GLuint vaoid;
		GLuint draw_cnt;

		GLuint model_cnt;			// added to check model count

		
		std::vector <glm::vec2> Position_Vertex;


		OpenGLModel() : primitive_type(0), primitive_cnt(0), vaoid(0), draw_cnt(0), model_cnt(0) {}
	};

	std::map<std::string, OpenGLModel>::iterator mdl_ref;
	std::map<std::string, OpenGLShader>::iterator shd_ref;

	// set up initial state
	static void Init(); 

	void Update(GLdouble delta_time);
	//static void OpenGLShadersInitialization();

	void Draw() const;

	void InitObjects();
	static void Cleanup();
//	static void Setup_Quad_VAO();
	static void init_scenes(std::string);
	static void Insert_Shader_Program(std::string shdr_pgm_name, std::string vtx_shdr_name, std::string frg_shdr_name);




	//Shaders
	static std::vector<OpenGLShader> shader;
	using VectorPairStrStr = std::vector <std::pair<std::string, std::string>>;
	static GLuint ShaderProgram;
	static std::map<std::string, OpenGLShader> shdrpgms;


	static void Load_Files();
	static void Load_Meshes();


	// Data for Square and Triangles
	static std::vector<glm::vec2> square;
	static std::vector<glm::vec2> triangle;
	static std::vector<std::string> mesh_Directory;
	
	static GLuint vaoID;
	static GLuint pboID;
	static GLuint textureID;


	//struct VAO_Object
	//{
	//	glm::vec2 Position;
	//	glm::vec3 Color;
	//	glm::vec2 Texture;
	//
	//	VAO_Object() : Position(0.0, 0.0), Color(0.0, 0.0, 0.0), Texture(0, 0) {}
	//
	//	void SetValue(float, float);
	//
	//	void SetTexture(float, float);
	//
	//};



	// Store Models inside:
	static std::map<std::string, OpenGLModel> Model_Storage;
	static std::map<std::string, OpenGLObject> Object_Storage;





private:




};

#endif // OPENGL_OBJECTS_H