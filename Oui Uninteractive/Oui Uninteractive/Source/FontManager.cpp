/**************************************************************************
 * @file FontManager.cpp
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 18-10-2023
 * @brief This source file contains the definition of the FontManager class used to setup FreeType and handle rendering of fonts
 *************************************************************************/

#include <iostream>
#include "FontManager.h"
#include "OpenGLObjects.h"
#include "OpenGLApplication.h"

// Create singleton for shader program, for shader usage.
//std::vector<OpenGLShader> OpenGLObject::shdrpgms;

// Initialize global pointer
FontManager* fontManager = nullptr;

/**************************************************************************
* @brief Default constructor for fontManager class
*************************************************************************/
FontManager::FontManager() {
	if (fontManager != nullptr) {
		// Instantiate sound system
		return;
	}
	else {
		fontManager = this;
	}
}


/**************************************************************************
* @brief Initializer for FontManager class
* @return No return
*************************************************************************/
void FontManager::Initialize() {
	result = FT_Init_FreeType(&ft); // Returns 0 if successful
	if (!result) {
		std::cout << "FreeType Library Initialization Successful" << std::endl;
	}


	
}


/**************************************************************************
* @brief Update function for the FontManager class
* @param dt - delta time
* @return No return
*************************************************************************/
void FontManager::Update(float dt) {

}


/**************************************************************************
* @brief This function handles rendering for the font system
* @return No return
*************************************************************************/
//void FontManager::RenderText(std::string text, float xPos, float yPos, float scale, float rot) 
void FontManager::RenderText(std::string text, float xPos, float yPos, float scale, glm::vec3 color) 
{
	// < TAKE NOTE THAT THIS IS BOTTOM LEFT RENDERING >
	
	// Loop through entire string
	OpenGLObject::shdrpgms[static_cast<int>(SHADER_ORDER::FONT)].Use();
	OpenGLObject::shdrpgms[static_cast<int>(SHADER_ORDER::FONT)].SetUniform("textColor", color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(OpenGLObject::VAO);
	
	for (std::string::const_iterator it = text.begin(); it != text.end(); it++) {
		// Find character with char key
		Character ch = charactersMap[*it];
		// Setup dimensions
		float renderX = xPos + ch.glyphBearing.x * scale;
		float renderY = yPos - (ch.glyphSize.y - ch.glyphBearing.y) * scale;
	
		float renderWidth = ch.glyphSize.x * scale;
		float renderHeight = ch.glyphSize.y * scale;
		// Render textured quad
		//texture = ch.glyphTexID
	
	
		// update VBO for each character
		float vertices[6][4] = {
			{ renderX,					renderY + renderHeight,		0.0f, 0.0f },
			{ renderX,					renderY,					0.0f, 1.0f },
			{ renderX + renderWidth,	renderY,					1.0f, 1.0f },
	
			{ renderX,					renderY + renderHeight,		0.0f, 0.0f },
			{ renderX + renderWidth,	renderY,					1.0f, 1.0f },
			{ renderX + renderWidth,	renderY + renderHeight,		1.0f, 0.0f }
		};
	
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.glyphTexID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, OpenGLObject::VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);        
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
	
		// Move cursor to next glyph
		xPos += (ch.advance >> 6) * scale;
	}
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	OpenGLObject::shdrpgms[static_cast<int>(SHADER_ORDER::FONT)].UnUse();
}


/**************************************************************************
* @brief This destructor handles shutdown of the font system
* @return No return
*************************************************************************/
FontManager::~FontManager() {

}

