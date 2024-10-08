#pragma once

class Actor;

class Camera {
public:
	Camera(float posX, float posY, float width, float height);

	float x, y;
	float width, height;

	void updateCamera(Actor* actor, float deltaTime);
};