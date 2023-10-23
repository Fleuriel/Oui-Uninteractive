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
		/*FMOD::Sound* newSound;
		result = system->createSound(i.path().string().c_str(), FMOD_DEFAULT, 0, &newSound);
		if (result != FMOD_OK) {
			std::cout << "FMOD error: " << FMOD_ErrorString(result);
		}
		bgmSounds.push_back(newSound);*/
		FT_Face newFace;
		result = FT_New_Face(ft, i.path().string().c_str(), 0, &newFace);
		if (!result) {
			std::cout << "Successfully loaded font: " << i.path().filename().string() << std::endl;
		}
	}
}


/**************************************************************************
* @brief This destructor handles shutdown of the font system
* @return No return
*************************************************************************/
FontManager::~FontManager() {

}