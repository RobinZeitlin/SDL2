#include "LevelEditor.h"

#include "../../Game.h"
#include "../../game/terrain/LoadLevel.h"

void LevelEditor::place_actor(glm::vec2 alignedPos)
{
	if (currentlySelectedName == "cube") {
		auto actor = new Block();
		game->loadLevel->place_actor(alignedPos, actor);
	} else if (currentlySelectedName == "dirt") {
		auto actor = new GrassBlock();
		game->loadLevel->place_actor(alignedPos, actor);
	} else if (currentlySelectedName == "enemy") {
		auto actor = new Enemy();
		game->loadLevel->place_actor(alignedPos, actor);
	} else if (currentlySelectedName == "playerspawnpoint") {
		auto actor = new SpawnPoint();
		game->loadLevel->place_actor(alignedPos, actor);
	}
}

void LevelEditor::spawn_camera()
{
	cameraController = new CameraController(this, game->loadLevel);
	game->spawnActor(cameraController, glm::vec2(0));

	load_textures();
	load_levels();
}

void LevelEditor::load_textures() {
	for (const auto& entry : std::filesystem::directory_iterator(texturesFolderPath))
	{
		if (entry.is_regular_file())
		{
			SDL_Surface* tempSurface = IMG_Load(entry.path().string().c_str());
			auto newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
			SDL_FreeSurface(tempSurface);

			std::string textureName = entry.path().stem().string();
			textures[textureName] = newTexture;
		}
	}
}
void LevelEditor::load_levels() {
	for (const auto& entry : std::filesystem::directory_iterator(levelFolderPath))
	{
		if (entry.is_regular_file())
		{
			std::string levelName = entry.path().stem().string();
			levelNames.push_back(levelName);
			std::cout << "Found level: " << levelName << std::endl;
		}
	}
}

void LevelEditor::render(SDL_Renderer* renderer) {
	render_level_editor_ui();
	render_spline_ui();

	selectionBar->render_selection_bar();
	
}
void LevelEditor::update(float dt) {
	if (cameraController != nullptr) {
		cameraController->update(dt);
	}
}

void LevelEditor::render_level_editor_ui() {
	ImGui::Begin("Level Editor");

	render_level_list();
	render_settings();
	render_block_selection();

	if (bGrid)
		render_grid();

	ImGui::End();
}
void LevelEditor::render_level_list() {
	ImGui::SeparatorText("File Handling");

	std::vector<const char*> levelNamePtrs;
	for (const std::string& name : levelNames) {
		levelNamePtrs.push_back(name.c_str());
	}

	ImGui::Text("Selected -> %s", levelNamePtrs[listbox_item_current]);

	ImGui::ListBox("<-", &listbox_item_current, levelNamePtrs.data(), static_cast<int>(levelNamePtrs.size()), 4);

	if (ImGui::Button("Save Current Level"))
	{
		std::cout << "Level Saved!" << std::endl;
		game->loadLevel->save_level(levelFolderPath + levelNamePtrs[listbox_item_current]);
	}

	if (ImGui::Button("Load Current Level"))
	{
		std::cout << "Level Loaded!" << std::endl;
		game->loadLevel->load_level_file(levelFolderPath + levelNamePtrs[listbox_item_current], false);
	}
}
void LevelEditor::render_settings() {
	ImGui::SeparatorText("Settings");

	ImGui::Checkbox("Grid", &bGrid);

	ImGui::SliderInt("Grid Size", &gridSize, 0, 100);
}
void LevelEditor::render_block_selection() {
	ImGui::SeparatorText("Building");

	const ImVec2 buttonSize = { 50 , 50 };

	ImGui::Text("Selected Block");
	ImGui::Image((ImTextureID)currentlySelected, buttonSize);
	ImGui::Text("Block List");

	for (const auto& [textureName, texture] : textures) {
		if (ImGui::ImageButton(textureName.c_str(), (ImTextureID)texture, buttonSize))
		{
			currentlySelected = texture;
			currentlySelectedName = textureName;
		}

		((std::distance(textures.begin(), textures.find(textureName)) + 1) % 2 == 0) ? ImGui::NewLine() : ImGui::SameLine();
	}

	ImGui::NewLine();
}
void LevelEditor::render_spline_ui() {
	ImGui::Begin("Spline Editor");
	ImGui::SeparatorText("Camera Spline");

	splinePointLabels.clear();

	ImGui::Checkbox("Loop", &game->spline->loopSpline);

	int i = 0;
	for (const auto& point : game->spline->splinePoints) {
		splinePointLabels.push_back("X: " + std::to_string((int)point->transform.position.x) + " - Y: " + std::to_string((int)point->transform.position.y));
	}

	std::vector<const char*> splinePointPtrs;
	for (const std::string& label : splinePointLabels) {
		splinePointPtrs.push_back(label.c_str());
	}

	ImGui::ListBox(" ", &listbox_spline_point_current, splinePointPtrs.data(), static_cast<int>(splinePointPtrs.size()), 4);

	ImGui::SameLine();

	if (ImGui::Button("-")) {
		game->spline->remove_spline_point();
	}

	ImGui::SameLine();

	if (ImGui::Button("+")) {
		game->spline->add_spline_point();
	}

	ImGui::End();
}
void LevelEditor::render_grid() {
	SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);

	for (int x = 0; x < gridSize; x++)
	{
		glm::vec2 start = { x * 32, 0 };
		glm::vec2 end = { x * 32, gridSize * 32 };

		SDL_RenderDrawLine(renderer,
			start.x - camera->x,
			start.y - camera->y,
			end.x - camera->x,
			end.y - camera->y);
	}

	for (int y = 0; y < gridSize; y++)
	{
		glm::vec2 start = { 0, y * 32 };
		glm::vec2 end = { gridSize * 32, y * 32 };

		SDL_RenderDrawLine(renderer,
			start.x - camera->x,
			start.y - camera->y,
			end.x - camera->x,
			end.y - camera->y);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

SplinePoint* LevelEditor::is_over_splinepoint(glm::vec2 mousePos)
{
	for (SplinePoint* point : game->spline->splinePoints) {
		if (point->transform.get_distance(point->transform.position, mousePos) < point->transform.scale.x) {
			
			selectedSplinePoint = point;
			return point;
		}
	}
	return nullptr;
}
