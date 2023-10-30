/**************************************************************************
 * @file AssetManager.cpp
 * @author Aaron Chan Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the implementation of the AssetManager 
 *        class, which is responsible for handling asset management. It 
 *        includes functionality to load, free, and reload various types of 
 *        assets, such as textures, sounds, and fonts, for use in the project.
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
#include "FontManager.h"


namespace fs = std::filesystem;


/**************************************************************************
 * @brief Constructor for the AssetManager class.
 * @param None.
 * @return None.
 *************************************************************************/
AssetManager::AssetManager()
{
}

/**************************************************************************
 * @brief Destructor for the AssetManager class.
 * @param None.
 * @return None.
 *************************************************************************/
AssetManager::~AssetManager()
{
    assetManager.FreeAll();
}

/**************************************************************************
 * @brief Loads all assets, including textures, sounds, and fonts.
 * @param None.
 * @return None.
 *************************************************************************/
void AssetManager::LoadAll() {
    std::cout 
    << ((AssetManager::LoadTextures()) ? "Textures loaded successfully" : "Failed to load textures") << std::endl
    << ((AssetManager::LoadSounds()) ? "Sounds loaded successfully" : "Failed to load sounds") << std::endl
    << ((AssetManager::LoadFonts()) ? "Fonts loaded successfully" : "Failed to load fonts") << std::endl;
}

/**************************************************************************
 * @brief Frees all loaded assets, including textures and sounds.
 * @param None.
 * @return None.
 *************************************************************************/
void AssetManager::FreeAll() {
    std::cout 
    << ((AssetManager::FreeTextures()) ? "Textures cleared successfully" : "Failed to clear textures") << std::endl
    << ((AssetManager::FreeSounds()) ? "Sounds freed successfully" : "Failed to free sounds") << std::endl;

}

/**************************************************************************
 * @brief Reloads all assets, including textures and sounds.
 * @param None.
 * @return None.
 *************************************************************************/
void AssetManager::ReloadAll() {
    std::cout 
    << ((AssetManager::ReloadTextures()) ? "Textures reloaded successfully" : "Failed to reload textures") << std::endl
    << ((AssetManager::ReloadSounds()) ? "Sounds reloaded successfully" : "Failed to reload sounds") << std::endl;
}

/**************************************************************************
 * @brief Loads textures from the specified directory.
 * @param None.
 * @return bool - true if textures are loaded successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::LoadTextures() {

    std::string directoryPath = "assets/texture"; // Change this to the directory of texture folder

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
 * @brief Sets up a texture and returns its handler.
 * @param std::string filePath of the Texture.
 * @return int Texture Handler.
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

/**************************************************************************
 * @brief Get a texture by its name.
 * @param std::string name - the name of the texture to retrieve.
 * @return int Texture handler.
 *************************************************************************/
int AssetManager::GetTexture(std::string name) {
    return textures[name];
}

/**************************************************************************
 * @brief Frees all loaded textures.
 * @param None.
 * @return bool - true if textures are freed successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::FreeTextures() {
    textures.clear();
    // Return true if the container size is 0, false otherwise.
    return textures.empty();
}

/**************************************************************************
 * @brief Reloads all textures.
 * @param None.
 * @return bool - true if textures are reloaded successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::ReloadTextures() {
    // Return true if free and load successfully
    return (AssetManager::FreeTextures() && AssetManager::LoadTextures());
}

/**************************************************************************
 * @brief Loads sounds, both background music (BGM) and sound effects (SFX).
 * @param None.
 * @return bool - true if both BGM and SFX are loaded successfully, 
                  false if there is an error.
*************************************************************************/
bool AssetManager::LoadSounds() {
    bool bgmResult = AssetManager::LoadBGM();
    bool sfxResult = AssetManager::LoadSFX();
    std::cout << ((bgmResult) ? "BGM loaded successfully" : "Failed to load BGM") << std::endl;
    std::cout << ((sfxResult) ? "SFX loaded successfully" : "Failed to load SFX") << std::endl;
    return (bgmResult && sfxResult);
}

/**************************************************************************
 * @brief Loads background music (BGM) from the specified directory.
 * @param None.
 * @return bool - true if BGM is loaded successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::LoadBGM() {

    // BGM file path
    std::filesystem::path bgmPath{ "assets/sounds/bgm" };

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

/**************************************************************************
 * @brief Loads sound effects (SFX) from the specified directory.
 * @param None.
 * @return bool - true if SFX are loaded successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::LoadSFX() {

    // SFX file path
    std::filesystem::path sfxPath{ "assets/sounds/sfx" };

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

/**************************************************************************
 * @brief Get a background music (BGM) by its index.
 * @param int index - the index of the BGM to retrieve.
 * @return FMOD::Sound* - a pointer to the BGM.
 *************************************************************************/
FMOD::Sound* AssetManager::GetBGM(int index) {
    // Return BGM
    return bgmSounds[index];
}

/**************************************************************************
 * @brief Get a sound effect (SFX) by its index.
 * @param int index - the index of the SFX to retrieve.
 * @return FMOD::Sound* - a pointer to the SFX.
 *************************************************************************/
FMOD::Sound* AssetManager::GetSFX(int index) {
    // Return SFX
    return sfxSounds[index];
}

/**************************************************************************
 * @brief Frees all loaded sounds, including both BGM and SFX.
 * @param None.
 * @return bool - true if both BGM and SFX are freed successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::FreeSounds() {
    // Free BGM & SFX
    bool bgmFreeResult{ AssetManager::FreeBGM() }, sfxFreeResult{ AssetManager::FreeSFX() };
    // Print results
    std::cout << ((bgmFreeResult) ? "BGM freed successfully" : "Failed to free BGM") << std::endl;
    std::cout << ((sfxFreeResult) ? "SFX freed successfully" : "Failed to free SFX") << std::endl;
    // Return overall results
    return (bgmFreeResult && sfxFreeResult);
}

/**************************************************************************
 * @brief Frees all loaded background music (BGM).
 * @param None.
 * @return bool - true if BGM is freed successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::FreeBGM() {
    // Free individual BGM sounds
    for (const auto& i : bgmSounds)
        i->release();

    // Empty BGM container
    bgmSounds.clear();

    // Return true if the container size is 0, false otherwise.
    return bgmSounds.empty();
}

/**************************************************************************
 * @brief Frees all loaded sound effects (SFX).
 * @param None.
 * @return bool - true if SFX are freed successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::FreeSFX() {
    // Free individual SFX sounds
    for (const auto& i : sfxSounds)
        i->release();

    // Empty SFX container
    sfxSounds.clear();

    // Return true if the container size is 0, false otherwise.
    return sfxSounds.empty();
}

/**************************************************************************
 * @brief Reloads all background music (BGM).
 * @param None.
 * @return bool - true if BGM is reloaded successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::ReloadBGM() {
    return (AssetManager::FreeBGM() && AssetManager::LoadBGM());
}

/**************************************************************************
 * @brief Reloads all sound effects (SFX).
 * @param None.
 * @return bool - true if SFX are reloaded successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::ReloadSFX() {
    return (AssetManager::FreeSFX() && AssetManager::LoadSFX());
}

/**************************************************************************
 * @brief Reloads all sounds, both BGM and SFX.
 * @param None.
 * @return bool - true if both BGM and SFX are reloaded successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::ReloadSounds() {
    // Return true if free and load successfully
    return (AssetManager::FreeSounds() && AssetManager::LoadSounds());

    // Reload BGM & SFX
    bool bgmReloadResult{ AssetManager::ReloadBGM() }, sfxReloadResult{ AssetManager::ReloadSFX() };
    // Print results
    std::cout << ((bgmReloadResult) ? "BGM reloaded successfully" : "Failed to reload BGM") << std::endl;
    std::cout << ((sfxReloadResult) ? "SFX reloaded successfully" : "Failed to reload SFX") << std::endl;
    // Return overall results
    return (bgmReloadResult && sfxReloadResult);
}


/**************************************************************************
 * @brief Loads fonts from the specified directory.
 * @param None.
 * @return bool - true if fonts are loaded successfully, 
                  false if there is an error.
*************************************************************************/
bool AssetManager::LoadFonts() {

    // File paths to the respetive fonts
    std::filesystem::path fontPath{ "assets/fonts/" };

    bool result{ true };

    if (fs::is_directory(fontPath)) {
        for (const auto& entry : fs::directory_iterator(fontPath)) {
            FT_Face newFace;
            fontManager->result = FT_New_Face(fontManager->ft, entry.path().string().c_str(), 0, &newFace);
            if (!fontManager->result)
                std::cout << "Successfully loaded font: " << entry.path().filename().string() << std::endl;
            fonts.push_back(newFace);
        }
    }
    else {
        // Print error
        std::cout << "The specified font path is not a directory." << std::endl;
        result = false;
    }

    // Set font sizes
    FT_Set_Pixel_Sizes(assetManager.GetFont(0), 0, 48);
    // Disable byte alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Load 128 chars of ASCII
    for (unsigned char ch = 0; ch < 128; ch++) {
        // Load the glyphs
        if (FT_Load_Char(assetManager.GetFont(0), ch, FT_LOAD_RENDER)) { // Returns non 0 if fail
            std::cout << "Character load failure: '" << ch << "'" << std::endl;
            continue;
        }
        // Generate individual textures
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            assetManager.GetFont(0)->glyph->bitmap.width,
            assetManager.GetFont(0)->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            assetManager.GetFont(0)->glyph->bitmap.buffer
        );
        // Texture settings
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Store character
        FontManager::Character character = {
            tex,
            glm::vec2(assetManager.GetFont(0)->glyph->bitmap.width, assetManager.GetFont(0)->glyph->bitmap.rows),
            glm::vec2(assetManager.GetFont(0)->glyph->bitmap_left, assetManager.GetFont(0)->glyph->bitmap_top),
            assetManager.GetFont(0)->glyph->advance.x
        };
        fontManager->charactersMap.insert(std::pair<char, FontManager::Character>(ch, character));
    }
    std::cout << "Characters successfully loaded" << std::endl;
    // Free up faces
    FT_Done_Face(assetManager.GetFont(0));
    // Free FreeType
    FT_Done_FreeType(fontManager->ft);

    return result;
}

/**************************************************************************
 * @brief Get a font by its index.
 * @param int index - the index of the font to retrieve.
 * @return FT_Face - a pointer to the font.
 *************************************************************************/
FT_Face AssetManager::GetFont(int index) {
    return fonts[index];
}

/**************************************************************************
 * @brief Frees loaded fonts.
 * @param None.
 * @return bool - true if fonts are freed successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::FreeFonts() {
    return true;
}

/**************************************************************************
 * @brief Reloads fonts.
 * @param None.
 * @return bool - true if fonts are reloaded successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::ReloadFonts() {
    return true;
}
