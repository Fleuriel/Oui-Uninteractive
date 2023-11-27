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
#include "SystemManager.h"
#include "Editor.h"

// Create singleton for shader program, for shader usage.
//std::vector<OpenGLShader> OpenGLObject::shdrpgms;

// Initialize global pointer
FontManager* fontManager = nullptr;

/**************************************************************************
* @brief Default constructor for fontManager class
*************************************************************************/
FontManager::FontManager() {
	if (fontManager != nullptr) {
		// Instantiate font system
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
	if (sysManager->isPaused == false) {
		(void)dt;
	}
}


/**************************************************************************
* @brief This function handles rendering for the font system
* @return No return
*************************************************************************/
void FontManager::RenderText(std::string fontName, std::string text, float xPos, float yPos, float scale, glm::vec3 color) 
{
	// < TAKE NOTE THAT THIS IS BOTTOM LEFT RENDERING >
	
	// Loop through entire string
	// Use Font shader
	OpenGLObject::shdrpgms[static_cast<int>(SHADER_ORDER::FONT)].Use();
	// Set font Shadering
	OpenGLObject::shdrpgms[static_cast<int>(SHADER_ORDER::FONT)].SetUniform("textColor", color.x, color.y, color.z);
	// Bind active texture to Texture0 
	glActiveTexture(GL_TEXTURE0);
	// Bind Vertex Array to The OpenGLObject's VAO
	glBindVertexArray(OpenGLObject::VAO);
	
	// Search for corresponding character map
	std::map<std::string, std::map<char, FontManager::Character>>::iterator fontMapIt = assetManager.GetFont(fontName);
	if (assetManager.FontFound(fontMapIt)) {
		// Loop through entire string
		for (std::string::const_iterator it = text.begin(); it != text.end(); it++) {
			// Find char key within char map
			char charKey = *it;
			auto charMapIt = fontMapIt->second.find(charKey);
			// Access specific char within specific font
			if (charMapIt != fontMapIt->second.end()) {
				// Find character with char key
				Character ch = charMapIt->second;


				// Setup dimensions
				float positionX = xPos, positionY = yPos;
				
				positionX += windowSize.first / 2;
				positionY += windowSize.second / 2;
				//																 /\
				//																/__\
				// Set to middle of the font (i.e. A, will be between both the /    \ )
				//																 ^ Middle here

				positionX -= 15 * static_cast<int>(text.size());

				positionX -= OpenGLObject::cameraObject.posX / 1.3;
				positionY -= OpenGLObject::cameraObject.posY / 1.3;

				float renderX = positionX + ch.glyphBearing.x * scale;
				float renderY = positionY - (ch.glyphSize.y - ch.glyphBearing.y) * scale;

				float renderWidth = ch.glyphSize.x * scale;
				float renderHeight = ch.glyphSize.y * scale;

				// Render textured quad
				// Update VBO for each character
				float vertices[6][4] = {
					{ renderX,					renderY + renderHeight,		0.0f, 0.0f },
					{ renderX,					renderY,					0.0f, 1.0f },
					{ renderX + renderWidth,	renderY,					1.0f, 1.0f },

					{ renderX,					renderY + renderHeight,		0.0f, 0.0f },
					{ renderX + renderWidth,	renderY,					1.0f, 1.0f },
					{ renderX + renderWidth,	renderY + renderHeight,		1.0f, 0.0f }
				};

				// Render glyph texture over quad
				glBindTexture(GL_TEXTURE_2D, ch.glyphTexID);
				// Update content of VBO memory
				glBindBuffer(GL_ARRAY_BUFFER, OpenGLObject::VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				// Render quad
				glDrawArrays(GL_TRIANGLES, 0, 6);
				// Move cursor to next glyph
				xPos += (ch.advance >> 6) * scale;
			}		
		}
	}
	else { // Invalid font name input
		std::cout << "Font file: " << fontName << " not found" << std::endl;
	}

	glBindVertexArray(0);
	// Unbind the Texture.
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// Unuse the font shader.
	OpenGLObject::shdrpgms[static_cast<int>(SHADER_ORDER::FONT)].UnUse();
}


/**************************************************************************
* @brief This destructor handles shutdown of the font system
* @return No return
*************************************************************************/
FontManager::~FontManager() {
	// Free freetype
	FT_Done_FreeType(fontManager->ft);
}

