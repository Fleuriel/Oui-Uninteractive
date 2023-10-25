/**************************************************************************
 * @file FontManager.h
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 18-10-2023
 * @brief This source file contains the decleration of the FontManager class used to setup FreeType and handle rendering of fonts
 *************************************************************************/
#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <GL/glew.h>
#include <string>
#include <filesystem>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "ISystem.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class FontManager : public ISystem {
public:
	FontManager();
	void Initialize();
	virtual void Update(float dt);
	void LoadFonts();
	~FontManager();
	
	// File paths to the respetive fonts
	std::filesystem::path fontPath{ "../fonts/" };
	// To store FreeType result codes
	int result; 
	// Container for fonts
	std::vector<FT_Face> fontVec{};

	// Struct to store character data
	struct Character {
		GLuint glyphTexID;
		glm::vec2 glyphSize;
		glm::vec2 glyphBearing; // Offset from baseline to top left of glyph
		GLuint advance; // Horizontal offset to next glyph
	};
	// Container for characters
	std::map<char, Character> charactersMap;
	
	void RenderText(); // Function to render text

private:
	FT_Library ft;

};
extern FontManager* fontManager;

#endif
