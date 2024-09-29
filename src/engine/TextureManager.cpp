#include "TextureManager.h"

TextureManager* textureManager = nullptr;

void TextureManager::init(SDL_Renderer* renderer)
{
    std::vector<std::string> loadStrings;
    std::string folderPath = std::filesystem::current_path().string() + "/src/assets/textures";

    for (const auto& entry : std::filesystem::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            std::string textureName = entry.path().stem().string();
            loadStrings.push_back(textureName);
            std::cout << "Found texture: " << textureName << std::endl; // Log each found texture
        }
    }

    for (const std::string& textureName : loadStrings)
    {
        loadTexture(textureName, renderer);
    }
}

void TextureManager::loadTexture(std::string textureName, SDL_Renderer* renderer)
{
    SDL_Surface* tempSurface = IMG_Load(("src/assets/textures/" + textureName + ".png").c_str());
    if (!tempSurface) {
        std::cerr << "Failed to load surface for texture: " << textureName
            << " Error: " << IMG_GetError() << std::endl;
        return;
    }

    auto newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!newTexture) {
        std::cerr << "Failed to create texture from surface: " << textureName
            << " Error: " << SDL_GetError() << std::endl;
        return;
    }

    textures[textureName] = newTexture;
}


