#include "LevelEditor.h"

#include "../../Game.h"

void LevelEditor::spawn_camera()
{
	cameraController = new CameraController();
	game->spawnActor(cameraController, glm::vec2(0));
}
