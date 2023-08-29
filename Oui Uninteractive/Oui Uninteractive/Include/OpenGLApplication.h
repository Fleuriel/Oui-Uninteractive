
#include <GL/glew.h> // for access to OpenGL API declarations 
#include <GLFW/glfw3.h>
#include <OpenGLShaders.h>




class OpenGLApplication {

public:

	// Functions to set data ...
	void OpenGLInit(short width, short height);
	void OpenGLUpdate();
	void OpenGLCleanup();
	void OpenGLWindowInitialization(GLFWwindow* window);
	void OpenGLObjectsInitialization();


// Models
public:

	struct OpenGLModels {

		GLenum primitive_type;
		GLuint primitive_cnt;
		GLuint vaoid;
		GLuint draw_cnt;
		GLuint model_cnt;

		OpenGLModels() : primitive_type(0), primitive_cnt(0), vaoid(0), draw_cnt(0), model_cnt(0) {}
	};

	// container for models and helper function(s) ...
	static std::vector<OpenGLApplication::OpenGLModels> models; // singleton
	static void init_models_cont(); // initialize singleton


public:

	struct OpenGLObjects {

		glm::vec2 scaling; // scaling
		GLfloat angle_speed, angle_disp; // orientation
		glm::vec2 position; // translation
		glm::mat3 mdl_to_ndc_xform;
		GLuint mdl_ref, shd_ref;

		// set up initial state
		void init();
		void draw() const;
		void update(GLdouble delta_time);



	};




};

