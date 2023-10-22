

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

}


/**************************************************************************
* @brief Update function for the FontManager class
* @param dt - delta time
* @return No return
*************************************************************************/
void FontManager::Update(float dt) {

}


/**************************************************************************
* @brief This destructor handles shutdown of the font system
* @return No return
*************************************************************************/
FontManager::~FontManager() {

}