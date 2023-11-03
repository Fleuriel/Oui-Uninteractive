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
#include "Filepaths.h"


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
    //assetManager.FreeAll();
}

/**************************************************************************
 * @brief Loads all assets, including textures, sounds, and fonts.
 * @param None.
 * @return None.
 *************************************************************************/
void AssetManager::LoadAll() {
    std::cout
        << ((AssetManager::LoadTextures()) ? "Textures loaded successfully" : "Failed to load textures") << std::endl
        << ((AssetManager::LoadSprites()) ? "Sprites loaded successfully" : "Failed to load sprites") << std::endl
        << ((AssetManager::LoadSounds()) ? "Sounds loaded successfully" : "Failed to load sounds") << std::endl
        << ((AssetManager::LoadFonts()) ? "Fonts loaded successfully" : "Failed to load fonts") << std::endl
        << ((AssetManager::LoadScenes()) ? "Scenes loaded successfully" : "Failed to load scenes") << std::endl;
}

/**************************************************************************
 * @brief Frees all loaded assets, including textures and sounds.
 * @param None.
 * @return None.
 *************************************************************************/
void AssetManager::FreeAll() {
    std::cout
        << ((AssetManager::FreeTextures()) ? "Textures freed successfully" : "Failed to free textures") << std::endl
        << ((AssetManager::FreeSprites()) ? "Sprites freed successfully" : "Failed to free sprites") << std::endl
        << ((AssetManager::FreeSounds()) ? "Sounds freed successfully" : "Failed to free sounds") << std::endl
        << ((AssetManager::FreeFonts()) ? "Fonts freed successfully" : "Failed to free fonts") << std::endl
        << ((AssetManager::FreeScenes()) ? "Scenes freed successfully" : "Failed to free scenes") << std::endl;

}

/**************************************************************************
 * @brief Reloads all assets, including textures and sounds.
 * @param None.
 * @return None.
 *************************************************************************/
void AssetManager::ReloadAll() {
    std::cout
        << ((AssetManager::ReloadTextures()) ? "Textures reloaded successfully" : "Failed to reload textures") << std::endl
        << ((AssetManager::ReloadSprites()) ? "Sprites reloaded successfully" : "Failed to reload Sprites") << std::endl
        << ((AssetManager::ReloadSounds()) ? "Sounds reloaded successfully" : "Failed to reload sounds") << std::endl
        << ((AssetManager::ReloadFonts()) ? "Fonts reloaded successfully" : "Failed to reload fonts") << std::endl
        << ((AssetManager::ReloadScenes()) ? "Scenes reloaded successfully" : "Failed to reload scenes") << std::endl;
}

/**************************************************************************
 * @brief Loads textures from the specified directory.
 * @param None.
 * @return bool - true if textures are loaded successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::LoadTextures() {

    //std::string directoryPath = "assets/texture"; // Change this to the directory of texture folder

    if (fs::is_directory(FILEPATH_TEXTURES)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_TEXTURES)) {
            std::string texFilePath = FILEPATH_TEXTURES + "/" + entry.path().filename().string();
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

Sprite::Sprite() {

}

Sprite::~Sprite() {

}

bool Sprite::SetTexture(int tex) {
    // Set the texture
    texture = tex;
    // Returns true if texture is not empty
    return !texture;
}

int Sprite::GetTexture() {
    // Returns the texture
    return texture;
}

bool Sprite::SetRowsAndColumns(int a, int b) {
    // Set the rows
    rows = a;
    // Set the columns
    columns = b;
    // Returns true if both rows and columns are non-zero
    return (rows && columns);
}

int Sprite::GetRows(){
    return rows;
}

int Sprite::GetColumns(){
    return columns;
}

bool Sprite::SetWidthAndHeight(int a, int b) {
    // Set the width
    width = a;
    // Set the height
    height = b;
    // Returns true if both width and height are non-zero
    return (width && height);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::SetTextureWidthAndHeight(int a, int b) {
    // Set the width
    texWidth = a;
    // Set the height
    texHeight = b;
    // Returns true if both width and height are non-zero
    return (texWidth && texHeight);
}

int Sprite::GetTextureWidth() {
    return texWidth;
}

int Sprite::GetTextureHeight() {
    return texHeight;
}

bool Sprite::AddCoordinates(int a, int b) {
    // Get the original size of the coordinates container
    size_t size = coordinates.size();
    // Store the new coordinates into the coordinates container
    coordinates.push_back(std::pair<int, int>(a, b));
    // Returns true if the coordinates container size increased (new coordinates sucessfully stored)
    return (coordinates.size() > size);
}

bool AssetManager::LoadSprites() {

    // if file path for sprites exist
    if (fs::is_directory(FILEPATH_SPRITES)) {
        // for every sprite in the file path
        for (const auto& entry : fs::directory_iterator(FILEPATH_SPRITES)) {
            // get the file path for the sprite
            std::string spriteFilePath = FILEPATH_SPRITES + "/" + entry.path().filename().string();
            //std::cout << "Sprite file " << spriteFilePath << " Found." << std::endl;

            // find the file extension 
            size_t extensionPos = entry.path().filename().string().find_last_of('.');
            // if file extension found
            if (extensionPos != std::string::npos) {

                // create new sprite class
                Sprite newsprite;
                
                // set the texture
                newsprite.SetTexture(AssetManager::SetUpTexture(spriteFilePath));
                //std::cout << textures[nameWithoutExtension] << " success!\n";

                // find '(' in the name
                size_t lBracketPos = entry.path().filename().string().find_last_of('(');

                // get the string containing rows and columns from the name
                std::string spriteRowsAndColumns = entry.path().filename().string().substr(lBracketPos + 1, extensionPos - lBracketPos - 2);
                //std::cout << spriteRowsAndColumns<<std::endl;

                // find the 'x' in the string that separates the rows and columns
                size_t xPos = spriteRowsAndColumns.find_last_of('x');

                // get the rows
                int rows = std::stoi(spriteRowsAndColumns.substr(0, xPos));
                //std::cout << rows << std::endl;
                
                // get the columns
                int columns = std::stoi(spriteRowsAndColumns.substr(xPos + 1));
                //std::cout << columns << std::endl;

                // set the rows and columns of the sprite
                newsprite.SetRowsAndColumns(rows, columns);

                // Bind the texture
                glBindTexture(GL_TEXTURE_2D, newsprite.GetTexture());

                // Get the width and height of the texture
                int texWidth, texHeight;
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texHeight);

                // Unbind the texture
                glBindTexture(GL_TEXTURE_2D, 0);

                // Store width and height of texture
                newsprite.SetTextureWidthAndHeight(texWidth, texHeight);
                //std::cout << "Texture Width : " << texWidth << std::endl << "Texture Height : " << texHeight << std::endl;

                // Store width and height of each "image" in texture
                newsprite.SetWidthAndHeight(newsprite.GetTextureWidth() / newsprite.GetColumns(), newsprite.GetTextureHeight() / newsprite.GetRows());
                //std::cout << "Width : " << newsprite.GetWidth() << std::endl << " Height : " << newsprite.GetHeight() << std::endl;

                // get the name of the sprite sheet
                std::string nameWithoutExtension = entry.path().filename().string().substr(0, lBracketPos);
                //std::cout << nameWithoutExtension << std::endl;

                // store the sprite in the sprite container
                sprites[nameWithoutExtension] = newsprite;
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

int AssetManager::GetSprite(std::string name) {
    return sprites[name].GetTexture();
}

bool AssetManager::FreeSprites() {
    sprites.clear();
    return sprites.empty();
}

bool AssetManager::ReloadSprites() {
    return (AssetManager::FreeSprites() && AssetManager::LoadSprites());
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
    //std::filesystem::path bgmPath{ "assets/sounds/bgm" };

    if (fs::is_directory(FILEPATH_SOUNDS_BGM)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_SOUNDS_BGM)) {
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
    //std::filesystem::path sfxPath{ "assets/sounds/sfx" };

    if (fs::is_directory(FILEPATH_SOUNDS_SFX)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_SOUNDS_SFX)) {
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
    //std::filesystem::path fontPath{ "assets/fonts/" };
    bool result{ true };
    if (fs::is_directory(FILEPATH_FONTS)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_FONTS)) {
            // Temp map to store currently loaded font glyphs            
            std::map<char, FontManager::Character> tempMap;

            // Load font typefaces
            FT_Face newFace;
            fontManager->result = FT_New_Face(fontManager->ft, entry.path().string().c_str(), 0, &newFace);
            if (!fontManager->result)
                std::cout << "Successfully loaded font: " << entry.path().filename().string() << std::endl;

            // Set font sizes for current font
            FT_Set_Pixel_Sizes(newFace, 0, 48);
            // Disable byte alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            // Load 128 chars of ASCII
            for (unsigned char ch = 0; ch < 128; ch++) {
                // Load the glyphs for current font
                if (FT_Load_Char(newFace, ch, FT_LOAD_RENDER)) { // Returns non 0 if fail
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
                    newFace->glyph->bitmap.width,
                    newFace->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    newFace->glyph->bitmap.buffer
                );
                // Texture settings
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // Store character
                GLuint advance = static_cast<GLuint>(static_cast<int>(newFace->glyph->advance.x));
                FontManager::Character character = {
                    tex,
                    glm::vec2(newFace->glyph->bitmap.width, newFace->glyph->bitmap.rows),
                    glm::vec2(newFace->glyph->bitmap_left, newFace->glyph->bitmap_top),
                    advance
                };
                // Insert chars of font into char map
                tempMap.insert(std::pair<char, FontManager::Character>(ch, character));
                // Insert entire map into master font container                
            }
            fontCharsMap.insert(std::make_pair(entry.path().filename().string(), tempMap));
            std::cout << entry.path().filename().string() << ", characters successfully loaded" << std::endl;
            // Free up faces
            FT_Done_Face(newFace);
        }
    }
    else {
        // Print error
        std::cout << "The specified font path is not a directory." << std::endl;
        result = false;
    }  
    return result;
}

std::map<std::string, std::map<char, FontManager::Character>>::iterator AssetManager::GetFont(std::string fontname) {
    return fontCharsMap.find(fontname);
}

/**************************************************************************
 * @brief Frees loaded fonts.
 * @param None.
 * @return bool - true if fonts are freed successfully, 
                  false if there is an error.
 *************************************************************************/
bool AssetManager::FreeFonts() {
    fontManager->individualCharMap.clear();
    return fontManager->individualCharMap.empty();
}

bool AssetManager::ReloadFonts() {
    return AssetManager::FreeFonts() && AssetManager::LoadFonts();
}

bool AssetManager::FontFound(std::map<std::string, std::map<char, FontManager::Character>>::iterator fontIter) {
    return fontIter != fontCharsMap.end();
}

bool AssetManager::LoadScenes() {
    bool result{true};
    if (fs::is_directory(FILEPATH_SCENES)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_SCENES)) {
            scenes.push_back(entry.path().filename().string());
        }
    }
    else {
        // Print error
        std::cout << "The specified scenes path is not a directory." << std::endl;
        result = false;
    }
    return result;
}

std::string AssetManager::GetScene(int index) {
    return scenes[index];
}

bool AssetManager::FreeScenes() {
    scenes.clear();
    return scenes.empty();
}

bool AssetManager::ReloadScenes() {
    return (AssetManager::FreeScenes() && AssetManager::LoadScenes());
}

int AssetManager::GetNumberOfScenes() {
    return scenes.size();
}