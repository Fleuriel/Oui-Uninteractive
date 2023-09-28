/**************************************************************************
 * @file Backgrounds.cpp
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/


#include <Background.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>


std::vector<OpenGLShader> Background::shdrpgms;

unsigned int Background::mdl_ref = 0; // Define and initialize mdl_ref
unsigned int Background::shd_ref = 0; // Define and initialize shd_ref

extern std::pair<int,int> windowSize;

GLuint Background::VAO = 0;
GLuint Background::VBO = 0;

int backgroundTexture;


/**************************************************************************
* @brief		Loads Meshes for models and/or other shader files to
*				enable creation of GameObjects.
* @param  none
* @return void
*************************************************************************/
void Background::Init()
{
#ifdef _DEBUG
	std::cout << "Background::Init()\n\n";

#endif // _DEBUG


	VectorPairStrStr fileName{
		std::make_pair<std::string, std::string>
		("../shaders/Oui_Uninteractive.vert", "../shaders/Oui_Uninteractive.frag")
	};



	init_shdrpgms_cont(fileName);
	
	bgTexture = Background::Setup_TextureObject("../texture/background.jpg");

	mdl_ref = 0;
	shd_ref = 0;

	position.x = 0;
	position.y = 0;

	using glm::radians;

	scaleModel.x = static_cast<float>(windowSize.first);
	scaleModel.y = static_cast<float>(windowSize.second);

	glm::mat3 Translate = glm::mat3
	{
		1, 0, 0,
		0, 1, 0,
		 position.x,  position.y, 1
	};

	// Compute the rotation matrix
	glm::mat3 Rotation = glm::mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);


	glm::mat3 Scale = glm::mat3
	{
		scaleModel.x, 0, 0,
		0, scaleModel.y, 0,
		0, 0, 1
	};

	float scaleX = 2.0f / windowSize.first;
	float scaleY = 2.0f / windowSize.second;

	glm::mat3 ScaleToWorldToNDC = glm::mat3
	{
		scaleX, 0, 0,
		0, scaleY, 0,
		0, 0, 1
	};

	model_To_NDC_xform = ScaleToWorldToNDC * Translate * Rotation * Scale;

#ifdef _DEBUG
	std::cout << '\n';
#endif

}


/**************************************************************************
* @brief		Updates each Background with Movement, Scale rotation.
*				Option for rotation has been added.
* 
* @param float  Acceleration of x-Axis
* @param float  Acceleration of y-Axis
* @param float  Scale on both X and Y axes. (Might need to change)
* @param float  Angle Rotation Speed
* @param bool   Boolean for Rotation Enable or Disable
* @return void
*************************************************************************/
void Background::Update(float newX, float newY, float scaleX, float scaleY)
{	

	//Scale the model based on float variable.
	scaleModel = glm::vec2(scaleX, scaleY);
	//Set the new position.
	position = glm::vec2(newX, newY);

	
	// Compute the scale matrix
	glm::mat3 Scale = glm::mat3(
		scaleModel.x, 0.0f, 0.0f,
		0.0f, scaleModel.y, 0.0f,
		0.0f, 0.0f, 1.0f
	);


	// Compute the rotation matrix
	glm::mat3 Rotation = glm::mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);


	// Compute the translation matrix
	glm::mat3 Translation = glm::mat3(
		1.0f, 0.0f, position.x,
		0.0f, 1.0f, position.y,
		0.0f, 0.0f, 1.0f
	);


	float valX = 2.0f / windowSize.first;
	float valY = 2.0f / windowSize.second;

	glm::mat3 ScaleToWorldToNDC = glm::mat3
	{
		valX, 0, 0,
		0, valY, 0,
		0, 0, 1
	};


	// Compute the model-to-world-to-NDC transformation matrix
	model_To_NDC_xform = ScaleToWorldToNDC * glm::transpose(Translation) * glm::transpose(Rotation)  * glm::transpose(Scale);

}


/**************************************************************************
* @brief		Draws the Background.
*				
* @param  none
* @return void
*************************************************************************/
void Background::Draw() const
{
	//texture object is to use texture image unit 6


	int tex{};
	switch (texID)
	{
	case 0:
		tex = bgTexture;
		break;
	default:
		break;
	}

	glBindTextureUnit(6, tex);

	shdrpgms[shd_ref].Use(); // Install the shader program




	shdrpgms[shd_ref].SetUniform("uTex2d", 6);
	// Part 2: Bind object's VAO handle
	glBindVertexArray(OpenGLObject::models[mdl_ref].vaoid); // Bind object's VAO handle

	// Part 3: Copy object's 3x3 model-to-NDC matrix to vertex shader
	GLint uniform_var_loc1 = glGetUniformLocation(shdrpgms[shd_ref].GetHandle(), "uModel_to_NDC");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(Background::model_To_NDC_xform));
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Part 4: Render using glDrawElements or glDrawArrays



	glDrawElements(
		OpenGLObject::models[mdl_ref].primitive_type,
		OpenGLObject::models[mdl_ref].draw_cnt,
		GL_UNSIGNED_SHORT, nullptr);




	// Part 5: Clean up
	glBindVertexArray(0); // Unbind the VAO
	shdrpgms[shd_ref].UnUse(); // Uninstall the shader program
}

void Background::Cleanup()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}



void Background::init_shdrpgms_cont(VectorPairStrStr const& vpss) {
	for (auto const& x : vpss) {
		std::vector<std::pair<GLenum, std::string>> shdr_files;
		shdr_files.emplace_back(std::make_pair(GL_VERTEX_SHADER, x.first));
		shdr_files.emplace_back(std::make_pair(GL_FRAGMENT_SHADER, x.second));
		OpenGLShader shdr_pgm;
		shdr_pgm.CompileLinkValidate(shdr_files);
		// insert shader program into container
		shdrpgms.emplace_back(shdr_pgm);
	}
}

int Background::Setup_TextureObject(std::string filePath)
{
	GLuint textureObj_Handler;

	int width, height, channels;
	unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (!image)
	{
		std::cout << "Failed to load texture: " << filePath << std::endl;
		return 0; // Return 0 to indicate failure
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &textureObj_Handler);
	glTextureStorage2D(textureObj_Handler, 1, GL_RGBA8, width, height);
	glTextureSubImage2D(textureObj_Handler, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image); // Free the image data after it's uploaded to OpenGL

	return textureObj_Handler;
}


