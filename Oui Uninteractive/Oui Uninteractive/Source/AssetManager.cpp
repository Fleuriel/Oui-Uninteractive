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
 *        assets, such as textures, sounds, fonts, etc, for use in the project.
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
#define NOMINMAX
#include <Windows.h>


namespace fs = std::filesystem;


std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

/**************************************************************************
 * @brief Constructor for the AssetManager class.
 *
 * This constructor initializes an instance of the AssetManager class.
 * It's responsible for managing assets such as textures, sounds, fonts,
 * and scenes used in your project.
 *
 * @param None.
 * @return None.
 *************************************************************************/
AssetManager::AssetManager()
{
}

/**************************************************************************
 * @brief Destructor for the AssetManager class.
 *
 * The destructor for the AssetManager class is responsible for releasing
 * and freeing any resources used by the AssetManager instance, such as
 * textures, sounds, and fonts.
 *
 * @param None.
 * @return None.
 *************************************************************************/
AssetManager::~AssetManager()
{
}

/**************************************************************************
 * @brief Loads all assets, including textures, sounds, fonts, and scenes.
 *
 * This function loads all the assets used in the project, including
 * textures, sounds, fonts, and scenes. It provides feedback about the
 * success or failure of each asset type load.
 *
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
 * @brief Frees all loaded assets, including textures, sounds, fonts, and scenes.
 *
 * This function frees all the previously loaded assets to release resources.
 * It provides feedback about the success or failure of each asset type release.
 *
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
 * @brief Reloads all assets, including textures, sounds, fonts, and scenes.
 *
 * This function reloads all the assets, effectively refreshing the assets.
 * It provides feedback about the success or failure of each asset type reload.
 *
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
 *
 * This function scans the specified directory for image files and loads them
 * as OpenGL textures. It supports common image formats such as PNG, JPEG, and
 * BMP. Each image file is loaded as a texture and stored for later use in the
 * application. The textures are associated with their respective filenames
 * (without file extensions) and stored in the 'textures' map for easy access.
 *
 * @param None.
 *
 * @return bool - Returns true if textures are loaded successfully, false if
 *               there is an error. It will return false if the specified
 *               directory doesn't exist or if there are any issues with
 *               loading the textures.
 *************************************************************************/
bool AssetManager::LoadTextures() {

    Currentlyloading = true;

    if (fs::is_directory(FILEPATH_TEXTURES)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_TEXTURES)) {
            std::string texFilePath = FILEPATH_TEXTURES + "/" + entry.path().filename().string();
            //std::cout << "Texture file " << texFilePath << " Found." << std::endl;
            
            size_t pos = entry.path().filename().string().find_last_of('.');
            if (pos != std::string::npos) {
                std::string nameWithoutExtension = entry.path().filename().string().substr(0, pos);
                //std::cout << nameWithoutExtension << std::endl;

                std::string Extension = entry.path().filename().string().substr(pos);
                //std::cout << Extension;
                std::string allowedExtensions = ".jpg,.jpeg,.png,.gif";

                // Check if the substring exists in the full string
                size_t found = allowedExtensions.find(toLowerCase(Extension));

                if (found == std::string::npos) {
                    std::string file(entry.path().filename().string());
                    std::wstring widefile(file.begin(), file.end());
                    HWND hwnd = GetActiveWindow();
                    std::string filepath(FILEPATH_TEXTURES);
                    // Convert std::string to std::wstring
                    std::wstring widefilepath(filepath.begin(), filepath.end());

                    std::wstring message = L"Incompatible file \"" + widefile + L"\" detected in \"" + widefilepath + L"\" folder!\n\nFile Deleted!";
                    LPCWSTR boxMessage = message.c_str();

                    MessageBox(hwnd, boxMessage, L"Load Failure", MB_OK | MB_ICONERROR);

                    // Construct the full destination path including the file name
                    fs::path destinationPath = FILEPATH_TRASHBIN / entry.path().filename();

                    // Perform the move operation
                    fs::rename(entry.path(), destinationPath);

                    continue;
                }
                

                textures[nameWithoutExtension] = AssetManager::SetUpTexture(texFilePath);
                std::cout << nameWithoutExtension << " success!\n";
            }
            else
                std::cout << "File " << entry.path().filename().string() << " is missing file extension.\n";
            
        }
        Currentlyloading = false;
        return true;
    }
    else {
        // Print error
        std::cout << "The specified path is not a directory." << std::endl;
        Currentlyloading = false;
        return false;
    }
}

/**************************************************************************
 * @brief Sets up a texture and returns its handler.
 *
 * This function takes a file path to an image, loads it as an OpenGL texture,
 * and returns the texture handler. It's used internally for loading textures.
 *
 * @param std::string filePath - The path to the texture image file.
 * @return int - The OpenGL texture handler.
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
 *
 * This function allows you to retrieve an OpenGL texture handler by providing
 * the name of the texture. The name should correspond to the filename of the
 * texture image (without the file extension) that was previously loaded using
 * the 'LoadTextures' function. If a texture with the specified name is found,
 * its handler is returned.
 *
 * @param std::string name - The name of the texture to retrieve.
 *
 * @return int - The OpenGL texture handler for the specified texture. If the
 *               texture with the given name is not found, it returns 0.
 *************************************************************************/
int AssetManager::GetTexture(std::string name) {
    return textures[name];
}

/**************************************************************************
 * @brief Frees all loaded textures.
 *
 * This function removes all textures that have been previously loaded using
 * the 'LoadTextures' function. It clears the 'textures' map, effectively
 * releasing the memory used for storing the textures. After calling this
 * function, the 'textures' map will be empty.
 *
 * @param None.
 *
 * @return bool - Returns true if textures are freed successfully, and the
 *               'textures' map is empty. Returns false if there is an error or
 *               if the map is not empty after the operation.
 *************************************************************************/
bool AssetManager::FreeTextures() {
    textures.clear();
    // Return true if the container size is 0, false otherwise.
    return textures.empty();
}

/**************************************************************************
 * @brief Reloads all textures.
 *
 * This function is used to reload all textures by first freeing the existing
 * textures and then loading them again using the 'LoadTextures' function. It
 * is a convenient way to refresh the textures in your application without
 * restarting the entire program.
 *
 * @param None.
 *
 * @return bool - Returns true if textures are reloaded successfully, and
 *               the 'textures' map is populated with the reloaded textures.
 *               Returns false if there is an error during the reload process.
 *************************************************************************/
bool AssetManager::ReloadTextures() {
    // Return true if free and load successfully
    return (AssetManager::FreeTextures() && AssetManager::LoadTextures());
}

/**************************************************************************
 * @brief Constructor for the Sprite class.
 *
 * This constructor initializes a new instance of the `Sprite` class. It sets
 * default values for various properties of the sprite, including the
 * texture, number of rows, columns, frame width, frame height, texture
 * width, texture height, and the container for storing bottom-left
 * coordinates.
 *
 * @param None.
 *
 * @return None.
 *************************************************************************/
Sprite::Sprite() {

}

/**************************************************************************
 * @brief Destructor for the Sprite class.
 *
 * This destructor is responsible for cleaning up resources associated with
 * an instance of the `Sprite` class. It is called when a `Sprite` object is
 * no longer needed, and it ensures the proper release of any resources
 * held by the sprite.
 *
 * @param None.
 *
 * @return None.
 *************************************************************************/
Sprite::~Sprite() {

}

/**************************************************************************
 * @brief Sets the texture to be used by the sprite.
 *
 * This method sets the texture to be used by the sprite to the provided
 * texture handler. It updates the internal texture property with the given
 * texture handler and returns true if the texture is set (non-empty).
 * Otherwise, it returns false.
 *
 * @param int tex - The texture handler to be set for the sprite.
 *
 * @return bool - true if the texture is set (non-empty), false otherwise.
 *************************************************************************/
bool Sprite::SetTexture(int tex) {
    // Set the texture
    texture = tex;
    // Returns true if texture is not empty
    return !texture;
}

/**************************************************************************
 * @brief Retrieves the texture handler used by the sprite.
 *
 * This method returns the texture handler currently used by the sprite.
 *
 * @param None.
 *
 * @return int - The texture handler used by the sprite.
 *************************************************************************/
int Sprite::GetTexture() {
    // Returns the texture
    return texture;
}

/**************************************************************************
 * @brief Sets the number of rows and columns for the sprite.
 *
 * This method sets the number of rows and columns for the sprite's animation frames.
 *
 * @param int a - The number of rows.
 * @param int b - The number of columns.
 *
 * @return bool - True if both rows and columns are set and non-zero, false otherwise.
 *************************************************************************/
bool Sprite::SetRowsAndColumns(int a, int b) {
    // Set the rows
    rows = a;
    // Set the columns
    columns = b;
    // Returns true if both rows and columns are non-zero
    return (rows && columns);
}

/**************************************************************************
 * @brief Retrieves the number of rows for the sprite's animation frames.
 *
 * This method returns the number of rows used in the sprite's animation frames.
 *
 * @return int - The number of rows.
 *************************************************************************/
int Sprite::GetRows(){
    return rows;
}

/**************************************************************************
 * @brief Retrieves the number of columns for the sprite's animation frames.
 *
 * This method returns the number of columns used in the sprite's animation frames.
 *
 * @return int - The number of columns.
 *************************************************************************/
int Sprite::GetColumns(){
    return columns;
}

/**************************************************************************
 * @brief Sets the frame width and height for the sprite.
 *
 * This method sets the width and height for the individual animation frames of the sprite.
 *
 * @param int a - The frame width.
 * @param int b - The frame height.
 * @return bool - true if both width and height are non-zero, false otherwise.
 *************************************************************************/
bool Sprite::SetWidthAndHeight(int a, int b) {
    // Set the width
    width = a;
    // Set the height
    height = b;
    // Returns true if both width and height are non-zero
    return (width && height);
}

/**************************************************************************
 * @brief Retrieves the frame width of the sprite.
 *
 * This method retrieves the width of the individual animation frames of the sprite.
 *
 * @return int - The frame width.
 *************************************************************************/
int Sprite::GetWidth() {
    return width;
}

/**************************************************************************
 * @brief Retrieves the frame height of the sprite.
 *
 * This method retrieves the height of the individual animation frames of the sprite.
 *
 * @return int - The frame height.
 *************************************************************************/
int Sprite::GetHeight() {
    return height;
}

/**************************************************************************
 * @brief Sets the texture width and height for the sprite.
 *
 * This method sets the width and height of the texture that the sprite uses.
 *
 * @param a - The width of the texture.
 * @param b - The height of the texture.
 * @return bool - True if both width and height are non-zero, false otherwise.
 *************************************************************************/
bool Sprite::SetTextureWidthAndHeight(int a, int b) {
    // Set the width
    texWidth = a;
    // Set the height
    texHeight = b;
    // Returns true if both width and height are non-zero
    return (texWidth && texHeight);
}

/**************************************************************************
 * @brief Retrieves the width of the texture used by the sprite.
 *
 * This method retrieves the width of the texture used by the sprite.
 *
 * @return int - The width of the texture.
 *************************************************************************/
int Sprite::GetTextureWidth() {
    return texWidth;
}

/**************************************************************************
 * @brief Retrieves the height of the texture used by the sprite.
 *
 * This method retrieves the height of the texture used by the sprite.
 *
 * @return int - The height of the texture.
 *************************************************************************/
int Sprite::GetTextureHeight() {
    return texHeight;
}

/**************************************************************************
 * @brief Stores bottom-left coordinates in the sprite's coordinate container.
 *
 * This method stores the specified bottom-left coordinates in the sprite's
 * coordinate container.
 *
 * @param a - The x-coordinate of the bottom-left position.
 * @param b - The y-coordinate of the bottom-left position.
 * @return bool - True if the coordinates were successfully added.
 *************************************************************************/
bool Sprite::AddCoordinates(int a, int b) {
    // Get the original size of the coordinates container
    size_t size = coordinates.size();
    // Store the new coordinates into the coordinates container
    coordinates.push_back(std::pair<int, int>(a, b));
    // Returns true if the coordinates container size increased (new coordinates sucessfully stored)
    return (coordinates.size() > size);
}

/**************************************************************************
 * @brief Loads sprite data from the specified directory and populates the 'sprites' container.
 *
 * This method scans the directory specified by FILEPATH_SPRITES for sprite files, creates Sprite
 * instances for each sprite file found, and stores them in the 'sprites' container.
 * Each sprite file is expected to follow the naming convention, including the number of rows
 * and columns in the sprite sheet, e.g., "example_sprite(2x3).png".
 *
 * @return True if the sprite data is loaded successfully, false if there was an error or the directory does not exist.
 *************************************************************************/
bool AssetManager::LoadSprites() {

    Currentlyloading = true;

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

                std::string Extension = entry.path().filename().string().substr(extensionPos);
                //std::cout << Extension;
                std::string allowedExtensions = ".png";

                // Check if the substring exists in the full string
                size_t found = allowedExtensions.find(toLowerCase(Extension));

                if (found == std::string::npos) {
                    std::string file(entry.path().filename().string());
                    std::wstring widefile(file.begin(), file.end());
                    HWND hwnd = GetActiveWindow();
                    std::string filepath(FILEPATH_SPRITES);
                    // Convert std::string to std::wstring
                    std::wstring widefilepath(filepath.begin(), filepath.end());

                    std::wstring message = L"Incompatible file \"" + widefile + L"\" detected in \"" + widefilepath + L"\" folder!\n\nFile Deleted!";
                    LPCWSTR boxMessage = message.c_str();

                    MessageBox(hwnd, boxMessage, L"Load Failure", MB_OK | MB_ICONERROR);

                    // Construct the full destination path including the file name
                    fs::path destinationPath = FILEPATH_TRASHBIN / entry.path().filename();

                    // Perform the move operation
                    fs::rename(entry.path(), destinationPath);

                    continue;
                }

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
        Currentlyloading = false;
        return true;
    }
    else {
        // Print error
        std::cout << "The specified path is not a directory." << std::endl;
        Currentlyloading = false;
        return false;
    }

}


/**************************************************************************
 * @brief Retrieves the texture ID associated with a sprite by its name.
 *
 * This function searches for a sprite with the specified name and returns
 * the associated texture ID. If the sprite does not exist, it returns 0.
 *
 * @param name The name of the sprite to retrieve the texture for.
 * @return The texture ID of the sprite or 0 if the sprite is not found.
 *************************************************************************/
Sprite AssetManager::GetSprite(std::string name) {
    return sprites[name];
}

int AssetManager::GetSpriteTexture(std::string name) {
    return GetSprite(name).GetTexture();
}

/**************************************************************************
 * @brief Clears the sprite container and frees associated resources.
 *
 * This function clears the sprite container, releasing any associated
 * resources, and returns true if the container is empty afterward.
 *
 * @return True if the sprite container is empty after clearing, false otherwise.
 *************************************************************************/
bool AssetManager::FreeSprites() {
    sprites.clear();
    return sprites.empty();
}

/**************************************************************************
 * @brief Reloads sprites by clearing the container and loading new ones.
 *
 * This function first clears the sprite container, releasing any associated
 * resources. Then, it loads new sprite assets. It returns true if both
 * clearing and loading are successful.
 *
 * @return True if sprites are successfully reloaded, false otherwise.
 *************************************************************************/
bool AssetManager::ReloadSprites() {
    return (AssetManager::FreeSprites() && AssetManager::LoadSprites());
}



/**************************************************************************
 * @brief Loads background music (BGM) and sound effects (SFX).
 *
 * This function loads both background music (BGM) and sound effects (SFX).
 * It calls the `LoadBGM` and `LoadSFX` functions to load these assets. It
 * also prints messages to the console to indicate the success or failure of
 * loading each type of sound.
 *
 * @return True if both BGM and SFX are loaded successfully, false otherwise.
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
 *
 * This function loads background music (BGM) from the directory specified
 * by `FILEPATH_SOUNDS_BGM`. It iterates through the files in the directory,
 * creates FMOD Sound objects for each BGM file, and adds them to the
 * `bgmSounds` container. If loading is successful, this function returns
 * true; otherwise, it returns false and prints any FMOD error messages.
 *
 * @return True if BGM is loaded successfully, false otherwise.
 *************************************************************************/
bool AssetManager::LoadBGM() {

    Currentlyloading = true;

    if (fs::is_directory(FILEPATH_SOUNDS_BGM)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_SOUNDS_BGM)) {

            // find the file extension 
            size_t extensionPos = entry.path().filename().string().find_last_of('.');

            std::string Extension = entry.path().filename().string().substr(extensionPos);
            //std::cout << Extension;
            std::string allowedExtensions = ".mp3,.wav,.ogg,.FLAC";

            // Check if the substring exists in the full string
            size_t found = allowedExtensions.find(toLowerCase(Extension));

            if (found == std::string::npos) {
                std::string file(entry.path().filename().string());
                std::wstring widefile(file.begin(), file.end());
                HWND hwnd = GetActiveWindow();
                std::string filepath(FILEPATH_SOUNDS_BGM);
                // Convert std::string to std::wstring
                std::wstring widefilepath(filepath.begin(), filepath.end());

                std::wstring message = L"Incompatible file \"" + widefile + L"\" detected in \"" + widefilepath + L"\" folder!\n\nFile Deleted!";
                LPCWSTR boxMessage = message.c_str();

                MessageBox(hwnd, boxMessage, L"Load Failure", MB_OK | MB_ICONERROR);

                // Construct the full destination path including the file name
                fs::path destinationPath = FILEPATH_TRASHBIN / entry.path().filename();

                // Perform the move operation
                fs::rename(entry.path(), destinationPath);

                continue;
            }

            FMOD::Sound* newSound;
            soundManager->result = soundManager->system->createSound(entry.path().string().c_str(), FMOD_DEFAULT, 0, &newSound);
            if (soundManager->result != FMOD_OK) {
                std::cout << "FMOD error: " << FMOD_ErrorString(soundManager->result);
                return false;
            }
            else {
                std::string fileName = entry.path().filename().string();
                soundMap[SoundManager::SoundType::BGM].insert(std::make_pair(fileName, newSound));
            }
        }
        Currentlyloading = false;
        return true;
    }
    else {
       // Print error
       std::cout << "The specified bgm path is not a directory." << std::endl;
       Currentlyloading = false;
       return false;
    }
}

/**************************************************************************
 * @brief Loads sound effects (SFX) from the specified directory.
 *
 * This function loads sound effects (SFX) from the directory specified
 * by `FILEPATH_SOUNDS_SFX`. It iterates through the files in the directory,
 * creates FMOD Sound objects for each SFX file, and adds them to the
 * `sfxSounds` container. If loading is successful, this function returns
 * true; otherwise, it returns false and prints any FMOD error messages.
 *
 * @return True if SFX is loaded successfully, false otherwise.
 *************************************************************************/
bool AssetManager::LoadSFX() {

    Currentlyloading = true;

    if (fs::is_directory(FILEPATH_SOUNDS_SFX)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_SOUNDS_SFX)) {

            // find the file extension 
            size_t extensionPos = entry.path().filename().string().find_last_of('.');

            std::string Extension = entry.path().filename().string().substr(extensionPos);
            //std::cout << Extension;
            std::string allowedExtensions = ".mp3,.wav,.ogg,.FLAC";

            // Check if the substring exists in the full string
            size_t found = allowedExtensions.find(toLowerCase(Extension));

            if (found == std::string::npos) {
                std::string file(entry.path().filename().string());
                std::wstring widefile(file.begin(), file.end());
                HWND hwnd = GetActiveWindow();
                std::string filepath(FILEPATH_SOUNDS_SFX);
                // Convert std::string to std::wstring
                std::wstring widefilepath(filepath.begin(), filepath.end());

                std::wstring message = L"Incompatible file \"" + widefile + L"\" detected in \"" + widefilepath + L"\" folder!\n\nFile Deleted!";
                LPCWSTR boxMessage = message.c_str();

                MessageBox(hwnd, boxMessage, L"Load Failure", MB_OK | MB_ICONERROR);

                // Construct the full destination path including the file name
                fs::path destinationPath = FILEPATH_TRASHBIN / entry.path().filename();

                // Perform the move operation
                fs::rename(entry.path(), destinationPath);

                continue;
            }

            FMOD::Sound* newSound;
            soundManager->result = soundManager->system->createSound(entry.path().string().c_str(), FMOD_DEFAULT, 0, &newSound);
            if (soundManager->result != FMOD_OK) {
                std::cout << "FMOD error: " << FMOD_ErrorString(soundManager->result);
                return false;
            }
            else {
                std::string fileName = entry.path().filename().string();
                soundMap[SoundManager::SoundType::SFX].insert(std::make_pair(fileName, newSound));
            }
        }
        Currentlyloading = false;
        return true;
    }
    else {
        // Print error
        std::cout << "The specified bgm path is not a directory." << std::endl;
        Currentlyloading = false;
        return false;
    }
}

/**************************************************************************
 * @brief Retrieves the FMOD Sound object for background music (BGM) at the specified index.
 *
 * This function returns the FMOD Sound object for the background music (BGM)
 * at the specified index in the `bgmSounds` container.
 *
 * @param index - The index of the BGM sound to retrieve.
 * @return The FMOD Sound object for the specified BGM, or nullptr if the index is out of bounds.
 *************************************************************************/
FMOD::Sound* AssetManager::GetBGM(std::string key) {
    // Return BGM
    return soundMap[SoundManager::SoundType::BGM][key];
}

/**************************************************************************
 * @brief Retrieves the FMOD Sound object for sound effects (SFX) at the specified index.
 *
 * This function returns the FMOD Sound object for a sound effect (SFX)
 * at the specified index in the `sfxSounds` container.
 *
 * @param index - The index of the SFX sound to retrieve.
 * @return The FMOD Sound object for the specified SFX, or nullptr if the index is out of bounds.
 *************************************************************************/
FMOD::Sound* AssetManager::GetSFX(std::string key) {
    // Return SFX
    return soundMap[SoundManager::SoundType::SFX][key];
}

/**************************************************************************
 * @brief Frees all loaded background music (BGM) and sound effects (SFX) resources.
 *
 * This function releases all the allocated resources for background music (BGM) and sound effects (SFX).
 *
 * @return True if all BGM and SFX resources are successfully freed, false otherwise.
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
 * @brief Frees all loaded background music (BGM) resources.
 *
 * This function releases all the allocated resources for background music (BGM) sounds.
 *
 * @return True if all BGM resources are successfully freed, false otherwise.
 *************************************************************************/
bool AssetManager::FreeBGM() {
    // Free individual BGM sounds
    for (const auto& i : soundMap[SoundManager::SoundType::BGM]) {
        FMOD::Sound* sound = i.second;
        sound->release();
    }  
    // Empty BGM container
    soundMap[SoundManager::SoundType::BGM].clear();

    // Return true if the container size is 0, false otherwise.
    return soundMap[SoundManager::SoundType::BGM].empty();
}

/**************************************************************************
 * @brief Frees all loaded sound effects (SFX) resources.
 *
 * This function releases all the allocated resources for sound effects (SFX) sounds.
 *
 * @return True if all SFX resources are successfully freed, false otherwise.
 *************************************************************************/
bool AssetManager::FreeSFX() {
    // Free individual SFX sounds
    for (const auto& i : soundMap[SoundManager::SoundType::SFX]) {
        FMOD::Sound* sound = i.second;
        sound->release();
    }
        

    // Empty SFX container
    soundMap[SoundManager::SoundType::SFX].clear();

    // Return true if the container size is 0, false otherwise.
    return soundMap[SoundManager::SoundType::SFX].empty();
}

/**************************************************************************
 * @brief Reloads background music (BGM) resources.
 *
 * This function unloads and reloads all the background music (BGM) resources.
 *
 * @return True if BGM resources are successfully reloaded, false otherwise.
 *************************************************************************/
bool AssetManager::ReloadBGM() {
    return (AssetManager::FreeBGM() && AssetManager::LoadBGM());
}

/**************************************************************************
 * @brief Reloads sound effects (SFX) resources.
 *
 * This function unloads and reloads all the sound effects (SFX) resources.
 *
 * @return True if SFX resources are successfully reloaded, false otherwise.
 *************************************************************************/
bool AssetManager::ReloadSFX() {
    return (AssetManager::FreeSFX() && AssetManager::LoadSFX());
}

std::map<SoundManager::SoundType, std::map<std::string, FMOD::Sound*>> AssetManager::GetSoundMap() {
    return assetManager.soundMap;
}

/**************************************************************************
 * @brief Reloads all sound resources, including BGM and SFX.
 *
 * This function unloads and reloads all sound resources, including background
 * music (BGM) and sound effects (SFX). It first unloads the existing resources,
 * then attempts to reload them. It prints the results of reloading BGM and SFX.
 *
 * @return True if both BGM and SFX are successfully reloaded, false otherwise.
 *************************************************************************/
bool AssetManager::ReloadSounds() {
    // Return true if free and load successfully
    // return (AssetManager::FreeSounds() && AssetManager::LoadSounds());

    // Reload BGM & SFX
    bool bgmReloadResult{ AssetManager::ReloadBGM() }, sfxReloadResult{ AssetManager::ReloadSFX() };
    // Print results
    std::cout << ((bgmReloadResult) ? "BGM reloaded successfully" : "Failed to reload BGM") << std::endl;
    std::cout << ((sfxReloadResult) ? "SFX reloaded successfully" : "Failed to reload SFX") << std::endl;
    // Return overall results
    return (bgmReloadResult && sfxReloadResult);
}


/**************************************************************************
 * @brief Loads fonts and their associated characters into memory.
 *
 * This function loads fonts from a specified directory and their associated
 * characters into memory. It generates textures for each character and stores
 * information about each character for rendering text.
 *
 * @return True if the fonts and characters are successfully loaded, false otherwise.
 *************************************************************************/
bool AssetManager::LoadFonts() {

    Currentlyloading = true;

    // File paths to the respetive fonts
    //std::filesystem::path fontPath{ "assets/fonts/" };
    bool result{ true };
    if (fs::is_directory(FILEPATH_FONTS)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_FONTS)) {


            // find the file extension 
            size_t extensionPos = entry.path().filename().string().find_last_of('.');

            std::string Extension = entry.path().filename().string().substr(extensionPos);
            //std::cout << Extension;
            std::string allowedExtensions = ".ttf,.otf";

            // Check if the substring exists in the full string
            size_t found = allowedExtensions.find(toLowerCase(Extension));

            if (found == std::string::npos) {
                std::string file(entry.path().filename().string());
                std::wstring widefile(file.begin(), file.end());
                HWND hwnd = GetActiveWindow();
                std::string filepath(FILEPATH_FONTS);
                // Convert std::string to std::wstring
                std::wstring widefilepath(filepath.begin(), filepath.end());

                std::wstring message = L"Incompatible file \"" + widefile + L"\" detected in \"" + widefilepath + L"\" folder!\n\nFile Deleted!";
                LPCWSTR boxMessage = message.c_str();

                MessageBox(hwnd, boxMessage, L"Load Failure", MB_OK | MB_ICONERROR);


                // Construct the full destination path including the file name
                fs::path destinationPath = FILEPATH_TRASHBIN / entry.path().filename();

                // Perform the move operation
                fs::rename(entry.path(), destinationPath);

                continue;
            }

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
    Currentlyloading = false;
    return result;
}

/**************************************************************************
 * @brief Retrieves an iterator to a font by its name.
 *
 * This function searches for a font with the given name in the fontCharsMap
 * and returns an iterator to it. You can use the iterator to access and
 * manipulate the font and its associated characters.
 *
 * @param fontname The name of the font to retrieve.
 * @return An iterator to the specified font, or fontCharsMap.end() if not found.
 *************************************************************************/
std::map<std::string, std::map<char, FontManager::Character>>::iterator AssetManager::GetFont(std::string fontname) {
    return fontCharsMap.find(fontname);
}

/**************************************************************************
 * @brief Frees the fonts and their associated characters.
 *
 * This function clears the individual character maps for all loaded fonts
 * and returns true if the character maps are empty after clearing, indicating
 * successful freeing of fonts and characters.
 *
 * @return True if the fonts and characters were successfully freed, false otherwise.
 *************************************************************************/
bool AssetManager::FreeFonts() {
    fontManager->individualCharMap.clear();
    return fontManager->individualCharMap.empty();
}

/**************************************************************************
 * @brief Reloads fonts and their associated characters.
 *
 * This function first frees the currently loaded fonts and their associated
 * characters by calling `AssetManager::FreeFonts`. Then, it loads the fonts
 * from the specified directory and their corresponding character sets using
 * `AssetManager::LoadFonts`. It returns true if both freeing and loading
 * were successful, indicating a successful font reload.
 *
 * @return True if fonts and characters were successfully reloaded, false otherwise.
 *************************************************************************/
bool AssetManager::ReloadFonts() {
    return AssetManager::FreeFonts() && AssetManager::LoadFonts();
}

/**************************************************************************
 * @brief Checks if a font is found in the font characters map.
 *
 * This function takes an iterator to a font within the font characters map
 * and checks if the font is found (i.e., it is not equal to the `end` iterator).
 *
 * @param fontIter An iterator to a font within the font characters map.
 * @return True if the font is found, false if not found.
 *************************************************************************/
bool AssetManager::FontFound(std::map<std::string, std::map<char, FontManager::Character>>::iterator fontIter) {
    return fontIter != fontCharsMap.end();
}

/**************************************************************************
 * @brief Loads the scene filenames from the specified directory.
 *
 * This function scans the directory specified by FILEPATH_SCENES and retrieves
 * the filenames of all scenes found in that directory. It populates the 'scenes'
 * container with the filenames.
 *
 * @return True if the scenes were loaded successfully, false if there was an error.
 *************************************************************************/
bool AssetManager::LoadScenes() {
    Currentlyloading = true;
    bool result{true};
    if (fs::is_directory(FILEPATH_SCENES)) {
        for (const auto& entry : fs::directory_iterator(FILEPATH_SCENES)) {

            // find the file extension 
            size_t extensionPos = entry.path().filename().string().find_last_of('.');

            std::string Extension = entry.path().filename().string().substr(extensionPos);
            //std::cout << Extension;
            std::string allowedExtensions = ".json";

            // Check if the substring exists in the full string
            size_t found = allowedExtensions.find(toLowerCase(Extension));

            if (found == std::string::npos) {
                std::string file(entry.path().filename().string());
                std::wstring widefile(file.begin(), file.end());
                HWND hwnd = GetActiveWindow();
                std::string filepath(FILEPATH_SCENES);
                // Convert std::string to std::wstring
                std::wstring widefilepath(filepath.begin(), filepath.end());

                std::wstring message = L"Incompatible file \"" + widefile + L"\" detected in \"" + widefilepath + L"\" folder!\n\nFile Deleted!";
                LPCWSTR boxMessage = message.c_str();

                MessageBox(hwnd, boxMessage, L"Load Failure", MB_OK | MB_ICONERROR);

                // Construct the full destination path including the file name
                fs::path destinationPath = FILEPATH_TRASHBIN / entry.path().filename();

                // Perform the move operation
                fs::rename(entry.path(), destinationPath);

                continue;
            }

            scenes.push_back(entry.path().filename().string());
        }
    }
    else {
        // Print error
        std::cout << "The specified scenes path is not a directory." << std::endl;
        result = false;
    }
    Currentlyloading = false;
    return result;
}

/**************************************************************************
 * @brief Retrieves the scene filename at the specified index.
 *
 * This function returns the filename of the scene located at the specified
 * index in the 'scenes' container.
 *
 * @param index - The index of the scene to retrieve.
 * @return The filename of the scene at the specified index.
 *************************************************************************/
std::string AssetManager::GetScene(int index) {
    return scenes[index];
}

/**************************************************************************
 * @brief Frees the 'scenes' container by clearing it.
 *
 * This function clears the 'scenes' container, removing all stored scene
 * filenames from memory.
 *
 * @return True if the 'scenes' container is empty after clearing, false
 *         otherwise.
 *************************************************************************/
bool AssetManager::FreeScenes() {
    scenes.clear();
    return scenes.empty();
}

/**************************************************************************
 * @brief Reloads the available scene filenames.
 *
 * This function reloads the available scene filenames by first freeing the
 * current list of scenes and then loading them again from the specified
 * directory.
 *
 * @return True if both the scenes are successfully freed and reloaded,
 *         false otherwise.
 *************************************************************************/
bool AssetManager::ReloadScenes() {
    return (AssetManager::FreeScenes() && AssetManager::LoadScenes());
}

/**************************************************************************
 * @brief Get the number of available scenes.
 *
 * This function returns the number of available scenes that have been
 * loaded into the AssetManager.
 *
 * @return The number of available scenes.
 *************************************************************************/
int AssetManager::GetNumberOfScenes() {
    return static_cast<int>(scenes.size());
}