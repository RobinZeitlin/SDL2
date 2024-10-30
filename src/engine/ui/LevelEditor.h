#pragma once

#include <ostream>
#include <iostream>
#include <string>

#include <SDL.h>

#include <filesystem>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include "../TextureManager.h"

#include "../../game/actors/CameraController.h"

class LevelEditor
{
public:
	LevelEditor(SDL_Renderer* gameRenderer, Camera* gameCamera) : renderer(gameRenderer), camera(gameCamera) { 
		spawn_camera();

		// shows a boring texture until the user has selected anything
		currentlySelected = textureManager->getTexture("cube");
	}

	void spawn_camera();

	void render();
	void update(float dt);

	void render_level_editor_ui();
	void render_grid();

	SDL_Texture* currentlySelected;

private:
	std::vector<std::string> levelNames;
	std::vector<SDL_Texture*> textures;

	std::string levelFolderPath = "src/levels/";
	std::string texturesFolderPath = "src/assets/textures/placeables/";

	SDL_Renderer* renderer;
	Camera* camera;

	CameraController* cameraController = nullptr;

	bool bGrid = true;
	int gridSize = 50;
	int listbox_item_current = 0;
};