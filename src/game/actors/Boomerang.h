#pragma once

#include "Actor.h"

class Boomerang : public Actor
{
public:
	Boomerang();

	void update(float dt);
	void render(SDL_Renderer* renderer, Camera* camera) override;

	void check_overlap();

	float getBounceDir();
	void launch_boomerang(glm::vec2 dir, float speed);

	void visualise_trajectory(SDL_Renderer* renderer, Camera* camera);

	float projectileSpeed = 0.0f;
	float visualRotation = 0.0f;
};