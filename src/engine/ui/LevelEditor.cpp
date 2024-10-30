#include "LevelEditor.h"

#include "../../Game.h"
#include "../../game/terrain/LoadLevel.h"

void LevelEditor::spawn_camera()
{
	cameraController = new CameraController();
	game->spawnActor(cameraController, glm::vec2(0));

	for (const auto& entry : std::filesystem::directory_iterator(levelFolderPath))
	{
		if (entry.is_regular_file())
		{
			std::string levelName = entry.path().stem().string();
			levelNames.push_back(levelName);
			std::cout << "Found level: " << levelName << std::endl;
		}
	}

	for (const auto& entry : std::filesystem::directory_iterator(texturesFolderPath))
	{
		if (entry.is_regular_file())
		{
			SDL_Surface* tempSurface = IMG_Load(entry.path().string().c_str());
			auto newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
			SDL_FreeSurface(tempSurface);

			textures.push_back(newTexture);
		}
	}
}

void LevelEditor::render()
{
	render_level_editor_ui();
}

void LevelEditor::update(float dt)
{
	if (cameraController != nullptr)
		cameraController->update(dt);
}

void LevelEditor::render_level_editor_ui()
{
	ImGui::Begin("Level Editor");

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

	ImVec2 buttonSize = { 50 , 50 };

	ImGui::SeparatorText("Settings");

	ImGui::Checkbox("Grid", &bGrid);

	ImGui::SliderInt("Grid Size", &gridSize, 0, 100);

	ImGui::SeparatorText("Building");

	ImGui::Text("Selected Block");
	ImGui::Image((ImTextureID)currentlySelected, buttonSize);
	ImGui::Text("Block List");

	int count = textures.size();

	for (int i = 0; i < count; i++) {
		if (ImGui::ImageButton((std::to_string(i)).c_str(), (ImTextureID)textures[i], buttonSize))
		{
			currentlySelected = textures[i];
			std::cout << currentlySelected << std::endl;
			std::cout << "Clicked button!" << std::endl;
		}

		if (i % 2 == 1 && i < count - 1) {
			ImGui::NewLine();
		}
		else {
			ImGui::SameLine();
		}
	}

	if (bGrid)
		render_grid();

	ImGui::End();
}

void LevelEditor::render_grid()
{
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
