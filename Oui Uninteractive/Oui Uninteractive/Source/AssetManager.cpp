/**************************************************************************
 * @file AssetManager.cpp
 * @author Aaron Chan Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
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
#include "Sound.h"


namespace fs = std::filesystem;



AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
    assetManager.FreeAll();
}

void AssetManager::LoadAll() {
    std::cout 
    << ((AssetManager::LoadTextures()) ? "Textures loaded successfully" : "Failed to load textures") << std::endl
    << ((AssetManager::LoadSounds()) ? "Sounds loaded successfully" : "Failed to load sounds") << std::endl;
}

void AssetManager::FreeAll() {
    std::cout 
    << ((AssetManager::FreeTextures()) ? "Textures cleared successfully" : "Failed to clear textures") << std::endl
    << ((AssetManager::FreeSounds()) ? "Sounds freed successfully" : "Failed to free sounds") << std::endl;

}

void AssetManager::ReloadAll() {
    std::cout 
    << ((AssetManager::ReloadTextures()) ? "Textures reloaded successfully" : "Failed to reload textures") << std::endl
    << ((AssetManager::ReloadSounds()) ? "Sounds reloaded successfully" : "Failed to reload sounds") << std::endl;
}

bool AssetManager::LoadTextures() {

    std::string directoryPath = "../texture"; // Change this to the directory of texture folder

    if (fs::is_directory(directoryPath)) {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            std::string texFilePath = directoryPath + "/" + entry.path().filename().string();
            //std::cout << "Texture file " << texFilePath << " Found." << std::endl;
            
            size_t pos = entry.path().filename().string().find_last_of('.');
            if (pos != std::string::npos) {
                std::string nameWithoutExtension = entry.path().filename().string().substr(0, pos);
                //std::cout << nameWithoutExtension << std::endl;

                textures[nameWithoutExtension] = AssetManager::SetUpTexture(texFilePath);
                //std::cout << textures[nameWithoutExtension] << " success!\n";
            }
            else
                std::cout << "File " << entry.path().filename().string() << " is missing file extension.\n";
            
        }
        return true;
    }
    else {
        // Print error
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
int AssetManager::SetUpTexture(std::string filePath) {
    GLuint textureObj_Handler; // OpenGL texture object handler

    int width, height, channels;

    // Load the image from the file using stb_image
    unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!image) {
        // If the image loading fails, print an error message and return 0 (failure)
        std::cout << "Failed to load texture: " << filePath << std::endl;
        return 0; // Return 0 to indicate failure
    }

    // Create an OpenGL texture object
    glCreateTextures(GL_TEXTURE_2D, 1, &textureObj_Handler);

    // Allocate storage for the texture with RGBA8 format
    glTextureStorage2D(textureObj_Handler, 1, GL_RGBA8, width, height);

    // Upload the image data to the texture object
    glTextureSubImage2D(textureObj_Handler, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Free the image data after it's uploaded to OpenGL
    stbi_image_free(image);

    // Return the OpenGL texture object handler
    return textureObj_Handler;
}

int AssetManager::GetTexture(std::string name) {
    return textures[name];
}

bool AssetManager::FreeTextures() {
    textures.clear();
    // Return true if the container size is 0, false otherwise.
    return textures.empty();
}

bool AssetManager::ReloadTextures() {
    // Return true if free and load successfully
    return (AssetManager::FreeTextures() && AssetManager::LoadTextures());
}

/**************************************************************************
* @brief This function loads the sounds from the file directories
* @return No return
*************************************************************************/
bool AssetManager::LoadSounds() {
    bool bgmResult = AssetManager::LoadBGM();
    bool sfxResult = AssetManager::LoadSFX();
    std::cout << ((bgmResult) ? "BGM loaded successfully" : "Failed to load BGM") << std::endl;
    std::cout << ((sfxResult) ? "SFX loaded successfully" : "Failed to load SFX") << std::endl;
    return (bgmResult && sfxResult);
}

bool AssetManager::LoadBGM() {

    // BGM file path
    std::filesystem::path bgmPath{ "../sounds/bgm" };

    if (fs::is_directory(bgmPath)) {
        for (const auto& entry : fs::directory_iterator(bgmPath)) {
            FMOD::Sound* newSound;
            soundManager->result = soundManager->system->createSound(entry.path().string().c_str(), FMOD_DEFAULT, 0, &newSound);
            if (soundManager->result != FMOD_OK)
                std::cout << "FMOD error: " << FMOD_ErrorString(soundManager->result);
            bgmSounds.push_back(newSound);
        }
        return true;
    }
    else {
        // Print error
        std::cout << "The specified bgm path is not a directory." << std::endl;
        return false;
    }
}

bool AssetManager::LoadSFX() {

    // SFX file path
    std::filesystem::path sfxPath{ "../sounds/sfx" };

    if (fs::is_directory(sfxPath)) {
        for (const auto& entry : fs::directory_iterator(sfxPath)) {
            FMOD::Sound* newSound;
            soundManager->result = soundManager->system->createSound(entry.path().string().c_str(), FMOD_DEFAULT, 0, &newSound);
            if (soundManager->result != FMOD_OK)
                std::cout << "FMOD error: " << FMOD_ErrorString(soundManager->result);
            sfxSounds.push_back(newSound);
        }
        return true;
    }
    else {
        // Print error
        std::cout << "The specified sfx path is not a directory." << std::endl;
        return false;
    }
}

FMOD::Sound* AssetManager::GetBGM(int index) {
    // Return BGM
    return bgmSounds[index];
}

FMOD::Sound* AssetManager::GetSFX(int index) {
    // Return SFX
    return sfxSounds[index];
}

bool AssetManager::FreeSounds() {
    // Free BGM & SFX
    bool bgmFreeResult{ AssetManager::FreeBGM() }, sfxFreeResult{ AssetManager::FreeSFX() };
    // Print results
    std::cout << ((bgmFreeResult) ? "BGM freed successfully" : "Failed to free BGM") << std::endl;
    std::cout << ((sfxFreeResult) ? "SFX freed successfully" : "Failed to free SFX") << std::endl;
    // Return overall results
    return (bgmFreeResult && sfxFreeResult);
}

bool AssetManager::FreeBGM() {
    // Free individual BGM sounds
    for (const auto& i : bgmSounds)
        i->release();

    // Empty BGM container
    bgmSounds.clear();

    // Return true if the container size is 0, false otherwise.
    return bgmSounds.empty();
}

bool AssetManager::FreeSFX() {
    // Free individual SFX sounds
    for (const auto& i : sfxSounds)
        i->release();

    // Empty SFX container
    sfxSounds.clear();

    // Return true if the container size is 0, false otherwise.
    return sfxSounds.empty();
}

bool AssetManager::ReloadSounds() {
    // Return true if free and load successfully
    return (AssetManager::FreeSounds() && AssetManager::LoadSounds());
}