#pragma once

#include <ostream>
#include <iostream>
#include <string>

#include <SDL.h>

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
	}

	void spawn_camera();

	void render() {
		render_level_editor_ui();
	}

	void update(float dt) {
		if (cameraController != nullptr)
			cameraController->update(dt);
	}

	void render_level_editor_ui()
	{
		ImGui::Begin("Level Editor");

		ImGui::SeparatorText("File Handling");

		const char* listbox_items[] = { "Level1", "Level2", "Level3", "Level4" };
		static int listbox_item_current = 0;

		ImGui::Text("Selected -> %s", listbox_items[listbox_item_current]);

		ImGui::ListBox("<-", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 2);

		if (ImGui::Button("Save Current Level"))
		{
			std::cout << "Clicked button!" << std::endl;
		}

		if (ImGui::Button("Load Current Level"))
		{
			std::cout << "Clicked button!" << std::endl;
		}

		ImVec2 buttonSize = { 50 , 50 };

		ImGui::SeparatorText("Settings");

		ImGui::Checkbox("Grid", &bGrid);

		ImGui::SliderInt("Grid Size", &gridSize, 0, 100);

		ImGui::SeparatorText("Building");

		ImGui::Text("Selected Block");
		ImGui::Image((ImTextureID)textureManager->getTexture("cube"), buttonSize);
		ImGui::Text("Block List");

		int count = 5;

		for (int i = 0; i < count; i++) {
			if (ImGui::ImageButton((std::to_string(i)).c_str(), (ImTextureID)textureManager->getTexture("cube"), buttonSize))
			{
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

	void render_grid()
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

	private:
		SDL_Renderer* renderer;
		Camera* camera;

		CameraController* cameraController = nullptr;

		bool bGrid = true;
		int gridSize = 50;
};