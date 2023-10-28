/**************************************************************************
 * @file AssetManager.cpp
 * @author Mark Low
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the definition of the AssetManager class used to handle asset management
 *************************************************************************/

#include <GL/glew.h>
#include <GL/GL.h>
#include <stb_image.h>
#include <map>
#include <string>
#include <filesystem>
#include <iostream>
#include "Background.h"
#include "AssetManager.h"

namespace fs = std::filesystem;



AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::Init() {
    std::cout << ((AssetManager::LoadTextures()) ? "Textures loaded successfully" : "Textures failed to load") << std::endl;
}

bool AssetManager::LoadTextures() {

    std::string directoryPath = "../texture"; // Change this to the directory you want to list files from

    if (fs::is_directory(directoryPath)) {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            std::string texFilePath = directoryPath + "/" + entry.path().filename().string();
            //std::cout << "Texture file " << texFilePath << " read." << std::endl;
            
            size_t pos = entry.path().filename().string().find_last_of('.');
            if (pos != std::string::npos) {
                std::string nameWithoutExtension = entry.path().filename().string().substr(0, pos);
                //std::cout << nameWithoutExtension << std::endl;
                //std::cout << "texfilepath : " << texFilePath;
                textures[nameWithoutExtension] = AssetManager::Setup_TextureObject(texFilePath);
                //std::cout << textures[nameWithoutExtension] << " success!\n";
            }
            else {
                #ifdef _DEBUG
                std::cout << "File " << entry.path().filename().string() << " is missing file extension.\n";
                #endif
            }
            
        }
        return true;
    }
    else {
        std::cout << "The specified path is not a directory." << std::endl;
        return false;
    }
}

/**************************************************************************
* @brief		Setup Texture Object into the parameters (int)
*
* @param  std::string filePath of the Texture.
* @return int	Texture Handler
*************************************************************************/
int AssetManager::Setup_TextureObject(std::string filePath) {
    // Create a int variable for texture Object
    GLuint textureObj_Handler;

    // width, height and channels for the image
    int width, height, channels;
    // Load the image into *image
    unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    // If no image is generated, failed.
    if (!image)
    {
        std::cout << "Failed to load texture: " << filePath << std::endl;
        return 0; // Return 0 to indicate failure
    }

    // Create Texture into Texture2D, reference to TextureObjHandler
    glCreateTextures(GL_TEXTURE_2D, 1, &textureObj_Handler);


    // Store the data into Storage2D
    glTextureStorage2D(textureObj_Handler, 1, GL_RGBA8, width, height);


    // Store the sub data into the sub Image
    glTextureSubImage2D(textureObj_Handler, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Free the image data after it's uploaded to OpenGL
    stbi_image_free(image);

    //
    std::cout << textureObj_Handler << '\n';

    // Return int value of a texture.
    return textureObj_Handler;
}

int AssetManager::GetTexture(std::string name) {
    return textures[name];
}