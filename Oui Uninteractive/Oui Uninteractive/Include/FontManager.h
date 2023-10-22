/**************************************************************************
 * @file FontManager.h
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the decleration of the FontManager class used to setup FreeType and handle rendering of fonts
 *************************************************************************/
#ifndef FONTMANAGER_H
#define FONTMANAGER_H


#include <filesystem>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "ISystem.h"



class FontManager : public ISystem {
public:
	FontManager();
	void Initialize();
	virtual void Update(float dt);

	~FontManager();
private:
	FT_Library ftLibrary{ nullptr };

};
extern FontManager* fontManager;

#endif
