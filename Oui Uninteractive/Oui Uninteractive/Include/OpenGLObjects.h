#ifndef OPENGL_OBJECTS_H
#define OPENGL_OBJECTS_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/GL.h>
#include <vector>
#include <map>
#include <string>

class OpenGLObject
{
public:
	
	glm::vec2 Scaling; // scaling
	GLfloat Angle_Speed, Angle_Displacement; // orientation
	glm::vec2 Position; // translation
	glm::mat3 Model_to_NDC_xform;
	GLuint mdl_ref, shd_ref;

	// set up initial state
	static void Init();
	static void Draw();
	static void Update(GLdouble delta_time);
	static void Cleanup();
	static void Setup_Quad_VAO();


	static void Load_Files();
	static void Load_Meshes();


	// Data for Square and Triangles
	static std::vector<glm::vec2> Square;
	static std::vector<glm::vec2> Triangle;
	static std::vector<std::string> Mesh_Directory;
	
	static GLuint vaoID;
	static GLuint pboID;
	static GLuint textureID;


	struct VAO_Object
	{
		glm::vec2 Position;
		glm::vec3 Color;
		glm::vec2 Texture;

		VAO_Object() : Position(0.0, 0.0), Color(0.0, 0.0, 0.0), Texture(0, 0) {}

		void SetValue(float, float);

		void SetTexture(float, float);

	};




	// encapsulates state required to render a geometrical model
	struct OpenGLModel {
		GLenum primitive_type;
		GLuint primitive_cnt;
		GLuint vaoid;
		GLuint draw_cnt;

		GLuint model_cnt;			// added to check model count

		OpenGLModel() : primitive_type(0), primitive_cnt(0), vaoid(0), draw_cnt(0), model_cnt(0) {}

		void init(std::string);	//Added function to initialize model ...

	};

	// Store Models inside:
	static std::map<std::string, OpenGLModel> Model_Storage;




private:




};

#endif // OPENGL_OBJECTS_H