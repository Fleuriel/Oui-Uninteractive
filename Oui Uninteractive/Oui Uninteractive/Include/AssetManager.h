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

class AssetManager
{
public:
	AssetManager();
	~AssetManager();
	void Init();

	bool LoadTextures();
	int Setup_TextureObject(std::string filePath);
	int GetTexture(std::string);

private:
	std::map<std::string, int> textures;
};

#endif
