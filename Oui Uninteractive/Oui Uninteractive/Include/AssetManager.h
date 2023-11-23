/**************************************************************************
 * @file AssetManager.h
 * @author Aaron Chan Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the declaration of the Sprite and 
		  AssetManager class used to handle asset management
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

	Sprite();										//constructor for sprite class
	~Sprite();										//destructor for sprite class

	bool SetTexture(int);							//sets the texture to be used
	int GetTexture();								//retrieves the texture to be used

	bool SetRowsAndColumns(int, int);				//sets the number of rows and columns
	int GetRows();									//retrieves the number of rows
	int GetColumns();								//retrieves the number of columns

	bool SetWidthAndHeight(int, int);				//sets the frame width and height
	int GetWidth();									//retrieves the frame width
	int GetHeight();								//retrieves the frame height
	
	bool SetTextureWidthAndHeight(int, int);		//sets the texture width and height
	int GetTextureWidth();							//retrieves the texture width
	int GetTextureHeight();							//retrieves the texture height

	bool AddCoordinates(int, int);					//stores coordinates into the coordinate container

private:
	int texture{};									//stores the texture to be used
	int rows{};										//stores number of rows
	int columns{};									//stores number of columns
	int frameNum{};									//stores frame index
	int width{};									//stores frame width
	int height{};									//stores frame height
	int texWidth{};									//stores texture width
	int texHeight{};								//stores texture height
	std::vector<std::pair<int, int>> coordinates{}; //stores bottom left coordinates
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
	bool LoadSprites();								//Function to load sprites
	bool FreeSprites();								//Function to free sprites
	bool ReloadSprites();							//Function to reload sprites


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
	bool LoadFonts();																			//Function to load fonts
	bool FreeFonts();																			//Function to free fonts
	bool ReloadFonts();																			//Function to reload fonts
	bool FontFound(std::map<std::string, std::map<char, FontManager::Character>>::iterator);	//Function to search if font exists


	// Scene functions
	bool LoadScenes();								//Function to load scenes
	bool FreeScenes();								//Function to free scenes
	bool ReloadScenes();							//Function to reload scenes
	int GetNumberOfScenes();						//Retrieves number of scenes

	// Access Asset functions
	int GetTexture(std::string);																	//Function to access textures
	Sprite GetSprite(std::string);																		//Function to access sprite's texture
	FMOD::Sound* GetBGM(std::string);																		//Function to access BGM sounds
	FMOD::Sound* GetSFX(std::string);																		//Function to access SFX Sounds
	std::map<std::string, std::map<char, FontManager::Character>>::iterator GetFont(std::string);	//Function to access fonts
	std::string GetScene(int);																		//Function to access scenes
	
	
private:
	//Containers	
	std::map<std::string, int> textures{};										//Container for textures
	std::map<std::string, Sprite> sprites{};									//Container for sprites
	std::map<std::string, FMOD::Sound*> bgmSounds{};							//Container for bgm sounds
	std::map<std::string, FMOD::Sound*> sfxSounds{};							//Container for sfx sounds
	std::map<std::string, std::map<char, FontManager::Character>> fontCharsMap; //Container for all glyphs for all fonts
	std::vector<std::string> scenes{};											//Container for scenes
};

extern AssetManager assetManager;

#endif
