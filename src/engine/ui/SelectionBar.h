#pragma once

#include <imgui.h>
#include <iostream>

class SelectionBar {
public:
	SelectionBar() { };

	void render_selection_bar()
	{
		ImGui::SetNextWindowSize(ImVec2(220, 60));

		ImGui::Begin("Selection Bar", nullptr, ImGuiWindowFlags_NoCollapse);

		// change to builder tool
		if (ImGui::Button("Build:[B]")) {
			std::cout << "Builder Tool Selected" << std::endl;
		}

		ImGui::SameLine();

		// change to spline tool
		if (ImGui::Button("Fill:[F]")) {
			std::cout << "Fill Tool Selected" << std::endl;
		}

		ImGui::End();
	};
};