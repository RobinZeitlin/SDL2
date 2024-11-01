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

#include "../../engine/ui/Spline.h"
#include "../../engine/ui/SelectionBar.h"

class LevelEditor
{
public:
	LevelEditor(SDL_Renderer* gameRenderer, Camera* gameCamera) : renderer(gameRenderer), camera(gameCamera) { 
		spawn_camera();

		// shows a boring texture until the user has selected anything
		std::string nameOfFile = "cube";
		currentlySelected = textureManager->getTexture(nameOfFile);
		currentlySelectedName = nameOfFile;

		spline = new Spline();
		selectionBar = new SelectionBar();
	}

	~LevelEditor() {
		levelNames.clear();
		splinePointLabels.clear();
		delete spline;
	}
	void spawn_camera();

	void render(SDL_Renderer* renderer);
	void update(float dt);

	void render_level_editor_ui();
	void render_spline_ui();
	void render_grid();

	SDL_Texture* currentlySelected;
	std::string currentlySelectedName;

private:
	std::vector<std::string> levelNames;
	std::vector<std::string> splinePointLabels;

	Spline* spline;
	SelectionBar* selectionBar;

	std::unordered_map<std::string, SDL_Texture*> textures;

	std::string levelFolderPath = "src/levels/";
	std::string texturesFolderPath = "src/assets/textures/placeables/";

	SDL_Renderer* renderer;
	Camera* camera;

	CameraController* cameraController = nullptr;

	bool bGrid = true;
	int gridSize = 50;
	int listbox_item_current = 0;
	int listbox_spline_point_current = 0;
};