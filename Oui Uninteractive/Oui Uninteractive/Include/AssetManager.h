/**************************************************************************
 * @file AssetManager.h
 * @author Mark Low
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the decleration of the AssetManager class used to handle asset management
 *************************************************************************/
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>
#include "FontManager.h"
#include <Sound.h>

class AssetManager
{
public:
	// General functions
	AssetManager();
	~AssetManager();
	void LoadAll();
	void FreeAll();
	void ReloadAll();

	// Texture functions
	bool LoadTextures();
	int SetUpTexture(std::string filePath);
	bool FreeTextures();
	bool ReloadTextures();
	

	// Sounds
	bool LoadSounds();
	bool LoadBGM();
	bool LoadSFX();
	bool FreeSounds();
	bool FreeBGM();
	bool FreeSFX();
	bool ReloadSounds();
	

	// Fonts
	bool LoadFonts();
	bool FreeFonts();
	bool ReloadFonts();


	// Access Assets
	int GetTexture(std::string);
	FMOD::Sound* GetBGM(int);
	FMOD::Sound* GetSFX(int);
	FT_Face GetFont(int);

private:
	//Containers
	std::map<std::string, int> textures{};
	std::vector<FMOD::Sound*> bgmSounds{};
	std::vector<FMOD::Sound*> sfxSounds{};
	std::vector<FT_Face> fonts{};
};

extern AssetManager assetManager;

#endif
