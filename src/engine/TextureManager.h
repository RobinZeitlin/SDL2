#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <unordered_map>
#include <filesystem>

#include "Debug.h";

class TextureManager
{
public:
	std::unordered_map<std::string, std::string> texturePaths;
	std::unordered_map<std::string, SDL_Texture*> textures;

	void init(SDL_Renderer* renderer);
	void loadTexture(std::string textureName, const std::string filePath, SDL_Renderer* renderer);

	SDL_Texture* getTexture(std::string fileName)
	{
		if (textures[fileName])
		{
			return textures[fileName];
		}

		std::cout << "no texture found" << std::endl;

		return nullptr;
	}
	std::unordered_map<std::string, SDL_Texture*> getAllTextures() {
		return textures;
	}
};

extern TextureManager* textureManager;