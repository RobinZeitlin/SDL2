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
#include "../../engine/ui/SplinePoint.h"
#include "../../engine/ui/SelectionBar.h"

class LevelEditor
{
public:
	LevelEditor(SDL_Renderer* gameRenderer, Camera* gameCamera) : renderer(gameRenderer), camera(gameCamera) { 
		spawn_camera();

		std::string nameOfFile = "cube";
		currentlySelected = textureManager->getTexture(nameOfFile);
		currentlySelectedName = nameOfFile;
		selectionBar = new SelectionBar();
	}

	~LevelEditor() {
		levelNames.clear();
		splinePointLabels.clear();

		delete cameraController;
	}

	void place_actor(glm::vec2 alignedPos);
	void spawn_camera();
	void load_textures();
	void load_levels();
	void render_level_list();
	void render_settings();
	void render_block_selection();

	void render(SDL_Renderer* renderer);
	void update(float dt);

	void render_level_editor_ui();
	void render_spline_ui();
	void render_grid();

	SplinePoint* is_over_splinepoint(glm::vec2 mousePos);
	SplinePoint* selectedSplinePoint;

	SDL_Texture* currentlySelected;
	std::string currentlySelectedName;

	CameraController* cameraController = nullptr;

private:
	std::vector<std::string> levelNames;
	std::vector<std::string> splinePointLabels;

	SelectionBar* selectionBar;

	std::unordered_map<std::string, SDL_Texture*> textures;

	SDL_Renderer* renderer;
	Camera* camera;

	const std::string levelFolderPath = "src/levels/";
	const std::string texturesFolderPath = "src/assets/textures/placeables/";

	bool bGrid = true;

	int gridSize = 50;
	
	// imgui
	int listbox_item_current = 0;
	int listbox_spline_point_current = 0;
};