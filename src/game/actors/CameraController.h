#pragma once

#include "Actor.h"

class CameraController : public Actor {
public:
	CameraController()
	{
		actorName = "Player";
        transform.position = glm::vec2(0);
	}

	void update(float dt) {
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
	}
};