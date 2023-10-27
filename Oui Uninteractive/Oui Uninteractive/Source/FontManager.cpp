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
	LoadFonts();
	
}


/**************************************************************************
* @brief Update function for the FontManager class
* @param dt - delta time
* @return No return
*************************************************************************/
void FontManager::Update(float dt) {

}


/**************************************************************************
* @brief This function loads the fonts from the file directories
* @return No return
*************************************************************************/
void FontManager::LoadFonts() {
	// Search font directory and load fonts
	for (const auto& i : std::filesystem::directory_iterator(fontPath)) {
		FT_Face newFace;
		result = FT_New_Face(ft, i.path().string().c_str(), 0, &newFace);
		if (!result) {
			std::cout << "Successfully loaded font: " << i.path().filename().string() << std::endl;
		}
		fontVec.push_back(newFace);
	}
	// Set font sizes
	FT_Set_Pixel_Sizes(fontVec[0], 0, 48);
	// Disable byte alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Load 128 chars of ASCII
	for (unsigned char ch = 0; ch < 128; ch++) {
		// Load the glyphs
		if (FT_Load_Char(fontVec[0], ch, FT_LOAD_RENDER)) { // Returns non 0 if fail
			std::cout << "Character load failure: '" << ch << "'" << std::endl;
			continue;
		}
		// Generate individual textures
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			fontVec[0]->glyph->bitmap.width,
			fontVec[0]->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			fontVec[0]->glyph->bitmap.buffer
		);
		// Texture settings
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Store character
		Character character = {
			tex,
			glm::vec2(fontVec[0]->glyph->bitmap.width, fontVec[0]->glyph->bitmap.rows),
			glm::vec2(fontVec[0]->glyph->bitmap_left, fontVec[0]->glyph->bitmap_top),
			fontVec[0]->glyph->advance.x
		};
		charactersMap.insert(std::pair<char, Character>(ch, character));
	}
	std::cout << "Characters successfully loaded" << std::endl;
	// Free up faces
	FT_Done_Face(fontVec[0]);
	// Free FreeType
	FT_Done_FreeType(ft);
}


/**************************************************************************
* @brief This function handles rendering for the font system
* @return No return
*************************************************************************/
void FontManager::RenderText(std::string text, float xPos, float yPos, float scale, float rot) {
	// Loop through entire string
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

		// Move cursor to next glyph
		xPos += (ch.advance >> 6) * scale;
	}
}


/**************************************************************************
* @brief This destructor handles shutdown of the font system
* @return No return
*************************************************************************/
FontManager::~FontManager() {

}