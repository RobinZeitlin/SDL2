#pragma once

#include "Actor.h"

class CameraController : public Actor {
public:
	CameraController()
	{
		actorName = "Player";
        transform.position = glm::vec2(0);
	}

	void update(float dt);
};