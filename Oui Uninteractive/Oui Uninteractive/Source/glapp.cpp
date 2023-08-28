/*!
@file		glapp.cpp
@author		pghali@digipen.edu
@coauthor	tan.a@digipen.edu
@date		26/05/2023

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and to extract function pointers
to OpenGL implementations.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <glapp.h>									//OpenGL libraries and addons
#include <glslshader.h>								//OpenGL libraries and addons
#include <glhelper.h>								//OpenGL libraries and addons
#include <glm/gtc/type_ptr.hpp>

#include <iostream>									// std::cout
#include <array>									// std::array
#include <string>									// std::string 
#include <iomanip>									// precision
#include <sstream>									// stringstream
#include <random>


/*                                                   objects with file scope
----------------------------------------------------------------------------- */

GLFWwindow* ptr_window;								// Declare ptr_window

std::string str;									// String to put to the title.

std::vector<GLSLShader> GLApp::shdrpgms{};			// Declaration of Vector Container of GLSL Shader
std::vector<GLApp::GLModel> GLApp::models{};			// Declaration of Vector Container of GLApp::GLModel
std::list<GLApp::GLObject> GLApp::objects{};			// Declaration of List GLApp::GLObject

//creating random seed and generator
std::random_device rd;// get random seed
std::default_random_engine random(rd());// Standard mersenne_twister_engine seeded with rd()


// Flag to check if the size() of the object container is max, according to MAX_OBJECTS
bool _isCapacityMax;

// Enumerator for Models (Rasterization)
enum polygonMode {

	MODE1, MODE2, MODE3
}pol_mode;


/*  _________________________________________________________________________*/
/*! float rand_uniform_float(float min, float max)

@brief
	This fucntion is used to get the random uniform float number.

@param min
		minimum value

@param max
		maximum value

@return uniform_real_distribution<float>
		a random float value that is between the min and max value.
*/
float rand_uniform_float(float min, float max)
{
	std::uniform_real_distribution<float> rand_float_value(min, std::nextafter(max, std::numeric_limits<float>::max()));
	return rand_float_value(random);
}

float rand_float(float min = 0.0f, float max = 1.0f)
{
	return min + ((max - min) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
}


int rand_int(int min, int max)
{
	std::uniform_int_distribution<int> rand_int_value(min, static_cast<int>(std::nextafter(max, std::numeric_limits<float>::max())));
	return rand_int_value(random);
}



/*  _________________________________________________________________________*/
/*! GLApp::init()
@brief
	This function is called to initialize values for GLApp

@return none

*/
void GLApp::init() {


	// Part 1: Initialize OpenGL state ...
	glClearColor(1.f, 1.f, 1.f, 1.f);

	// Part 2: use the entire window as viewport ...
	GLint w = GLHelper::width, h = GLHelper::height;
	glViewport(0, 0, w, h);

	// Part 3: create as many shared shader programs as required
	// handles to shader programs must be contained in GLApp::shdrpgms
	GLApp::VPSS shdr_file_names{ // vertex & fragment shader files
		std::make_pair<std::string, std::string>
		("../shaders/my-tutorial-3.vert", "../shaders/my-tutorial-3.frag")
	};

	GLApp::init_shdrpgms_cont(shdr_file_names);

	// Part 4: initialize as many geometric models as required
	// these geometric models must be contained in GLApp::models
	GLApp::init_models_cont();

	pol_mode = polygonMode::MODE1;
	_isCapacityMax = false;
}


/*  _________________________________________________________________________*/
/*! GLApp::GLObject::init()

@brief
	This function is called to initialize values for objects created with GLObject
	struct.

@return none

*/
void GLApp::GLObject::init() {

	GLObject::mdl_ref = rand_int(0, 1);
	GLObject::shd_ref = 0;

	GLObject::position = glm::vec2{ rand_uniform_float(-1.f,1.f) * static_cast<float>(WORLD_WIDTH / 2), // x axis
									rand_uniform_float(-1.f,1.f) * static_cast<float>(WORLD_HEIGHT / 2) // y axis
	};

	//std::cout << "pos x : " << position.x << ", " << "pos y : " << position.y << '\n';

	// initialize initial angular displacement and angular speed of object
	GLfloat const max_rotation_speed = 30.f;

	//current rotation
	GLObject::angle_disp = rand_float() * 360.f; //in degree

	//rotation speed
	GLObject::angle_speed = rand_float() * max_rotation_speed; //in degree

	GLfloat const min_scale = 450.f;
	GLfloat const max_scale = 450.f;

	GLObject::scaling = glm::vec2{ rand_float(min_scale,max_scale), rand_uniform_float(min_scale,max_scale) };

	glm::mat3 Translate = glm::mat3
	{
		1, 0, position.x,
		0, 1, position.y,
		0, 0, 1
	};

	glm::mat3 Rotation = glm::mat3
	{
		cosf(glm::radians(angle_disp)), -sinf(glm::radians(angle_disp)), 0,
		sinf(glm::radians(angle_disp)), cosf(glm::radians(angle_disp)), 0,
		0, 0, 1
	};

	glm::mat3 Scale = glm::mat3
	{
		scaling.x, 0, 0,
		0, scaling.y, 0,
		0, 0, 1
	};

	glm::mat3 ScaleToWorldToNDC = glm::mat3
	{
		1 / (WORLD_WIDTH / 2), 0, 0,
		0, 1 / (WORLD_WIDTH / 2), 0,
		0, 0, 1
	};

	//scaling not required to transpose. They be the same after transpose
	mdl_to_ndc_xform = ScaleToWorldToNDC * glm::transpose(Translate) * glm::transpose(Rotation) * Scale;
}


/*  _________________________________________________________________________*/
/*! GLApp::update()
@brief
	This function updates every frame

@return none

*/
void GLApp::update() {

	// Part 1: Update polygon rasterization mode ...
	// Check if key 'P' is pressed
	// If pressed, update polygon rasterization mode
	if (GLHelper::keystateP == GL_TRUE)
	{

		// Update the polygon mode based on the current mode (Switch Case)
		switch (pol_mode)
		{
		case polygonMode::MODE1:
			std::cout << "mode1\n";
			pol_mode = polygonMode::MODE2;
			break;
		case polygonMode::MODE2:
			std::cout << "mode2\n";
			pol_mode = polygonMode::MODE3;
			break;
		case polygonMode::MODE3:
			std::cout << "mode3\n";
			pol_mode = polygonMode::MODE1;
			break;
		}
		//Set keystateP (GLHelper) to GL_FALSE
		GLHelper::keystateP = GL_FALSE;
	}



	// Part 2: Spawn or kill objects ...
	// Check if left mouse button is pressed
	// If maximum object limit is not reached, spawn new object(s)
	// Otherwise, kill oldest objects
	if (GLHelper::LMouseState == GLFW_PRESS)
	{
		// Set LMouseState (GLHelper) to GL_FALSE
		GLHelper::LMouseState = GL_FALSE;

		// Check 1: Checks if object size is lesser than or equals to MAX_OBJECTS as set by the user (32768)
		// Check 2: Checks if _isCapacityMax is TRUE or FALSE
		if (GLApp::objects.size() <= MAX_OBJECTS && _isCapacityMax == false)
		{

			// Spawn new object(s)
			// Multiply the number of objects by 2
			size_t currentObjectCount = GLApp::objects.size();
			size_t newObjectCount = currentObjectCount * 2;

			// Spawn new objects
			for (size_t i = currentObjectCount; i < newObjectCount; i++)
			{
				GLApp::GLObject newObject{};


				newObject.init();
				GLApp::models[newObject.mdl_ref].model_cnt++;
				// ...
				GLApp::objects.emplace_back(newObject);
			}


			// Initial Number of Objects to spawn on first click.
			// Have to be below the previous if statement as C++ is a top to bottom language.

#ifdef _DEBUG
	// Checks for the object size and see if the object is properly multiplied by its previous number.
			std::cout << GLApp::objects.size() << '\n';
#endif
			if (GLApp::objects.size() == 0)
			{
				size_t numNewObjects = 1;
				for (size_t i = 0; i < numNewObjects; i++)
				{

					GLApp::GLObject newObject{};

					newObject.init();

					GLApp::models[newObject.mdl_ref].model_cnt++;
					// ...
					GLApp::objects.emplace_back(newObject);
				}
			}

			// Check: Checks if object size is equals to the MAX_OBJECTS
			if (GLApp::objects.size() >= MAX_OBJECTS)
			{
				_isCapacityMax = true;
			}
		}
		else if (GLApp::objects.size() != 0 && _isCapacityMax)
		{

			// Kill oldest objects
			size_t numObjectsToKill = GLApp::objects.size() / 2;  // Number of objects to kill

			for (size_t i = 0; i < numObjectsToKill; i++)
			{
				// if the container is not empty
				if (!GLApp::objects.empty())
				{
					// model count decrement
					GLApp::models[GLApp::objects.front().mdl_ref].model_cnt--;
					GLApp::objects.pop_front();  // Remove the oldest object from the front of the list
				}
			}

			// Flag to check if the size is 1
			if (GLApp::objects.size() == 1)
			{
				_isCapacityMax = false;
			}
		}
	}
	else
	{
		// Mouse button is not pressed
		// Empty for now
	}


	// Part 3:
	// for each object in container GLApp::objects
	// Update object's orientation
	// A more elaborate implementation would animate the object's movement
	// A much more elaborate implementation would animate the object's size
	// Using updated attributes, compute world-to-ndc transformation matrix
	for (GLApp::GLObject& obj : GLApp::objects)
		obj.update(GLHelper::delta_time);

}

/*  _________________________________________________________________________*/
/*! GLApp::draw()

@return none

This function draw into the viewport
*/
void GLApp::draw()
{


	// Set polygon mode based on the mode selector above.
	switch (pol_mode)
	{
	case polygonMode::MODE1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case polygonMode::MODE2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.0f);
		break;
	case polygonMode::MODE3:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPointSize(5.0f);
		break;
	}


	// Part 2: Clear back buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Part 4: Render each object in container GLApp::objects
	for (auto const& x : GLApp::objects) {
		x.draw(); // call member function GLObject::draw()
	}

	// Part 1: Write window title
	std::stringstream sStream;
	sStream  
		<< " | Obj: " << GLApp::objects.size()
		<< " | Box: " << GLApp::models[1].model_cnt
		<< " | Mystery: " << GLApp::models[0].model_cnt
		<< " | FPS: " << std::fixed << std::setprecision(2) << GLHelper::fps;
	std::string windowTitle = sStream.str();
	glfwSetWindowTitle(GLHelper::ptr_window, windowTitle.c_str());
}

/*  _________________________________________________________________________*/
/*! GLApp::GLObject::draw() const

@brief
	This function draw the object into the viewport

@return none

*/
void GLApp::GLObject::draw() const
{
	// Part 1: Install the shader program
	GLApp::shdrpgms[shd_ref].Use(); // Install the shader program

	// Part 2: Bind object's VAO handle
	glBindVertexArray(GLApp::models[mdl_ref].vaoid); // Bind object's VAO handle

	// Part 3: Copy object's 3x3 model-to-NDC matrix to vertex shader
	GLint uniform_var_loc1 = glGetUniformLocation(GLApp::shdrpgms[shd_ref].GetHandle(), "uModel_to_NDC");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(GLApp::GLObject::mdl_to_ndc_xform));
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Part 4: Render using glDrawElements or glDrawArrays
	glDrawElements(
		models[mdl_ref].primitive_type,
		models[mdl_ref].draw_cnt,
		GL_UNSIGNED_SHORT, NULL);

	// Part 5: Clean up
	glBindVertexArray(0); // Unbind the VAO
	GLApp::shdrpgms[shd_ref].UnUse(); // Uninstall the shader program
}

/*  _________________________________________________________________________*/
/*! GLApp::GLObject::update(GLdouble deltaTime)

@brief
	This function updates the GLObject object's physics (Scale, Rotation,
	Translation)

@param deltaTime
		the time per frame for each loop.

@return none

*/
void GLApp::GLObject::update(GLdouble deltaTime)
{
	GLObject::angle_disp += (GLObject::angle_speed * static_cast<float>(deltaTime));

	// Compute the angular displacement in radians


	// Compute the scale matrix
	glm::mat3 Scale = glm::mat3(
		scaling.x, 0.0f, 0.0f,
		0.0f, scaling.y, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the rotation matrix
	glm::mat3 Rotation = glm::mat3(
		cosf(glm::radians(GLObject::angle_disp)), -sinf(glm::radians(GLObject::angle_disp)), 0.0f,
		sinf(glm::radians(GLObject::angle_disp)), cosf(glm::radians(GLObject::angle_disp)), 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the translation matrix
	glm::mat3 Translation = glm::mat3(
		1.0f, 0.0f, position.x,
		0.0f, 1.0f, position.y,
		0.0f, 0.0f, 1.0f
	);


	// Compute the scaling matrix to map from world coordinates to NDC coordinates
	glm::mat3 ScaleToWorldToNDC = glm::mat3(
		1.0f / (WORLD_WIDTH / 2), 0.0f, 0.0f,
		0.0f, 1.0f / (WORLD_HEIGHT / 2), 0.0f,
		0.0f, 0.0f, 1.0f
	);


	// Compute the model-to-world-to-NDC transformation matrix
	mdl_to_ndc_xform = ScaleToWorldToNDC * glm::transpose(Translation) * glm::transpose(Rotation) * glm::transpose(Scale);
}

/*  _________________________________________________________________________*/
/*! GLModel::cleanup()
@brief
	This function cleans up the code to prevent memory leaks.


@return none
Empty for now

*/
void GLApp::cleanup() {
	// empty for now
}

/*  _________________________________________________________________________*/
/*! GLApp::GLModel GLApp::mystery_model()

@brief
	This function contains the mystery model of the tutorial.

@return none
*/

/*  _________________________________________________________________________*/
/*! GLApp::GLModel GLApp::box_model()


@return Model mdl
	Returns


This function contains the box model of the tutorial.

*/
GLApp::GLModel GLApp::box_model()
{
	std::vector<glm::vec2> pos_vtx
	{
		glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.5f),
			glm::vec2(-0.5f, 0.5f), glm::vec2(-0.5f, -0.5f)
	};

	std::default_random_engine dre(std::random_device{}());
	std::uniform_real_distribution<float> urdf(0.f, std::nextafter(1.f, std::numeric_limits<float>::max()));
	std::vector<glm::vec3> clr_vtx;

	for (size_t i{}; i < pos_vtx.size(); i++)
	{
		float red = urdf(dre);
		float blue = urdf(dre);
		float green = urdf(dre);

		glm::vec3 color_to_push = { red, green, blue };
		clr_vtx.push_back(color_to_push);
	}

	GLApp::GLModel mdl;
	// Allocating buffer objects
	// transfer vertex position and colowr attributes to VBO
	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);

	//Allocating and filling data store
	glNamedBufferStorage(vbo_hdl,
		sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec3) * clr_vtx.size(),
		nullptr, GL_DYNAMIC_STORAGE_BIT);
	//transfer vertex position data
	glNamedBufferSubData(vbo_hdl, 0,
		sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());
	//transfer vertex color data
	glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(),
		sizeof(glm::vec3) * clr_vtx.size(), clr_vtx.data());

	GLuint vaoid;
	// encapsulate information about contents of VBO and VBO handlee
	// to another object called VAO
	glCreateVertexArrays(1, &vaoid); // vaoid is data member of GLApp::GLModel

	// for vertex position array, we use vertex attribute index 8
	// and vertex buffer binding point 3
	glEnableVertexArrayAttrib(vaoid, 0);
	glVertexArrayVertexBuffer(vaoid, 3, vbo_hdl, 0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 0, 3);

	// Color Attributes
	// for vertex color array, we use vertex attribute index 9
	// and vertex buffer binding point 4
	glEnableVertexArrayAttrib(vaoid, 1);
	glVertexArrayVertexBuffer(vaoid, 4, vbo_hdl,
		sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec3));
	glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 1, 4);

	// represents indices of vertices that will define 2 triangles with
	// counterclockwise winding
	std::array<GLushort, 6> idx_vtx{
		0, 1, 2,  // 1st triangle with counterclockwise winding is specified by
		// vertices in VBOs with indices 0,1,2
		2, 3, 0	  // 2nd trinagle with counter clockwise winding 
	};

	GLuint idx_elem_cnt;
	//get the number of indices in the idx_vtx array
	idx_elem_cnt = idx_vtx.size();

	//allocate an element buffer object and fill it with data from idx_vtx
	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl);
	glNamedBufferStorage(ebo_hdl,
		sizeof(GLushort) * idx_elem_cnt,
		reinterpret_cast<GLvoid*>(idx_vtx.data()),
		GL_DYNAMIC_STORAGE_BIT);

	//attached the element buffer object to the vertex array object
	//and unbind the vertex array object
	glVertexArrayElementBuffer(vaoid, ebo_hdl);
	glBindVertexArray(0);

	mdl.vaoid = vaoid;
	mdl.primitive_type = GL_TRIANGLES;
	mdl.draw_cnt = idx_vtx.size();
	mdl.primitive_cnt = pos_vtx.size();
	return mdl;
}


/*  _________________________________________________________________________*/
/*! GLApp::init_models_cont()

@brief
	This function initialize the model container

@return none

*/
void GLApp::init_models_cont() {
	GLApp::models.emplace_back(GLApp::box_model());
}

/*  _________________________________________________________________________*/
/*! GLApp::init_shdrpgms_cont(GLApp::VPSS const& vpss)

@brief
	This function initialize the shader program container

@param vpss
	a typedef for the VPSS container which is of type
	std::vector<std::pair<std::string, std::string>>

@return none
*/
void GLApp::init_shdrpgms_cont(GLApp::VPSS const& vpss) {
	for (auto const& x : vpss) {
		std::vector<std::pair<GLenum, std::string>> shdr_files;
		shdr_files.emplace_back(std::make_pair(GL_VERTEX_SHADER, x.first));
		shdr_files.emplace_back(std::make_pair(GL_FRAGMENT_SHADER, x.second));
		GLSLShader shdr_pgm;
		shdr_pgm.CompileLinkValidate(shdr_files);
		// insert shader program into container
		GLApp::shdrpgms.emplace_back(shdr_pgm);
	}
}

