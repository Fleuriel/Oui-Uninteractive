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

class Sprite
{
public:

	Sprite();
	~Sprite();

	bool SetTexture(int);
	int GetTexture();

	bool SetRowsAndColumns(int, int);
	int GetRows();
	int GetColumns();

	bool SetWidthAndHeight(int, int);
	int GetWidth();
	int GetHeight();

	bool SetTextureWidthAndHeight(int, int);
	int GetTextureWidth();
	int GetTextureHeight();

	bool AddCoordinates(int, int);

private:
	int texture{};
	int rows{};
	int columns{};
	int width{};
	int height{};
	int texWidth{};
	int texHeight{};
	std::vector<std::pair<int, int>> coordinates{};
};


class AssetManager
{
public:

	// General functions
	AssetManager();									//Constructor for AssetManager class
	~AssetManager();								//Destructor for AssetManager class


	void LoadAll();									//Function to load all assets
	void FreeAll();									//Function to free all assets
	void ReloadAll();								//Function to reload all assets


	// Texture functions
	bool LoadTextures();							//Function to load textures
	int SetUpTexture(std::string filePath);			//Function to set up textures
	bool FreeTextures();							//Function to free textures
	bool ReloadTextures();							//Function to reload textures
	
	// Sprite functions
	bool LoadSprites();


	// Sound functions
	bool LoadSounds();								//Function to load sounds (BGM + SFX)
	bool LoadBGM();									//Function to load BGM sounds
	bool LoadSFX();									//Function to load SFX sounds
	bool FreeSounds();								//Function to free sounds (BGM + SFX)
	bool FreeBGM();									//Function to free BGM sounds
	bool FreeSFX();									//Function to free SFX sounds
	bool ReloadSounds();							//Function to reload sounds (BGM + SFX)
	bool ReloadBGM();								//Function to reload BGM sounds
	bool ReloadSFX();								//Function to reload SFX sounds
	

	// Font functions
	bool LoadFonts();								//Function to load fonts
	bool FreeFonts();								//Function to free fonts
	bool ReloadFonts();								//Function to reload fonts
	bool FontFound(std::map<std::string, std::map<char, FontManager::Character>>::iterator);


	// Access Asset functions
	int GetTexture(std::string);					//Function to access textures
	int GetSprite(std::string);
	FMOD::Sound* GetBGM(int);						//Function to access BGM sounds
	FMOD::Sound* GetSFX(int);						//Function to access SFX Sounds
	std::map<std::string, std::map<char, FontManager::Character>>::iterator GetFont(std::string);


private:
	//Containers
	std::map<std::string, int> textures{};
	std::map<std::string, Sprite> sprites{};
	std::vector<FMOD::Sound*> bgmSounds{};
	std::vector<FMOD::Sound*> sfxSounds{};
	std::map<std::string, std::map<char, FontManager::Character>> fontCharsMap; // This map stores all glyphs for all fonts
};

extern AssetManager assetManager;

#endif
