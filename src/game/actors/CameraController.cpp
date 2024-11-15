#include "CameraController.h"

#include "../../Game.h"
#include "../terrain/LoadLevel.h"

void CameraController::update(float dt)
{
    const float playerSpeed = 350.0f;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    if (currentKeyStates[SDL_SCANCODE_W]) {
        transform.position.y -= playerSpeed * dt;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        transform.position.y += playerSpeed * dt;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        transform.position.x -= playerSpeed * dt;
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        transform.position.x += playerSpeed * dt;
    }

    if (currentKeyStates[SDL_SCANCODE_C]) {
        crtEditorTool = CurrentEditorTool::BuilderTool;
    }
    if (currentKeyStates[SDL_SCANCODE_V]) {
        crtEditorTool = CurrentEditorTool::BucketTool;
    }
    if (currentKeyStates[SDL_SCANCODE_B]) {
        crtEditorTool = CurrentEditorTool::SplineTool;
    }

    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    glm::vec2 worldSpaceMousePos;

    worldSpaceMousePos.x = mouseX + game->camera->x;
    worldSpaceMousePos.y = mouseY + game->camera->y;

    glm::vec2 alignedPos = glm::vec2(
        (int((worldSpaceMousePos.x) / 32) * 32),
        (int((worldSpaceMousePos.y) / 32) * 32)
    );

    if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)) {
        if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
            game->loadLevel->destroy_actor(alignedPos);
        }
        if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            switch (crtEditorTool)
            {
            case CurrentEditorTool::BuilderTool:
                game->levelEditor->place_actor(alignedPos);
                break;

            case CurrentEditorTool::BucketTool:
                game->loadLevel->fill_tool(alignedPos);
                break;

            case CurrentEditorTool::SplineTool:
                auto clickedPoint = game->levelEditor->is_over_splinepoint(worldSpaceMousePos);
                break;
            }
        }
    }
}
