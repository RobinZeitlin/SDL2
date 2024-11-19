#include "Camera.h"
#include "game/actors/Actor.h"

Camera::Camera(float posX, float posY, float screenWidth, float screenHeight)
{
	x = posX;
	y = posY;
	width = screenWidth;
	height = screenHeight;
}

void Camera::updateCamera(glm::vec2 pos, float deltaTime)
{
    float actorX = pos.x + 32 / 2;
    float actorY = pos.y + 32 / 2;

	float newX = actorX - (width / 2);
	float newY = actorY - (height / 2);

	float cameraSpeed = 6.5f;

	x = glm::mix(x, newX, cameraSpeed * deltaTime);
    y = glm::mix(y, newY, cameraSpeed * deltaTime);
}
