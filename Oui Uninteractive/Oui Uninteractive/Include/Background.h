/**************************************************************************
 * @file OpenGLObjects.h
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/GL.h>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <OpenGLShaders.h>
#include <Vector2D.h>
#include <OpenGLObjects.h>


class Background
{
public:
	Background(){};
	
	~Background(){};

	glm::vec2 position;							// translation
	glm::vec2 scaleModel;						// Scale for the Model
	glm::mat3 model_To_NDC_xform;				// Model to NDC 
	static GLuint mdl_ref, shd_ref;				// Model and Shader Reference

	std::vector<GLuint> textures;				// integer for texture (stb returns integer).
	int texID;
	static GLuint VAO, VBO;						// Object VAO VBO


	// set up initial state
	void Init();

	void Update(float newX, float newY, float scaleX, float scaleY);

	void Draw() const;

	//Shaders
	static std::vector<OpenGLShader>shdrpgms;
	using VectorPairStrStr = std::vector <std::pair<std::string, std::string>>;
	


	static void init_shdrpgms_cont(VectorPairStrStr const& vpss);

	// Texture
	static int Setup_TextureObject(std::string filePath);

	static void Cleanup();


	// Data for Square and Triangles
	static std::vector<glm::vec2> square;
	static std::vector<glm::vec2> triangle;
	static std::vector<std::string> mesh_Directory;


private:
	
};

#endif 