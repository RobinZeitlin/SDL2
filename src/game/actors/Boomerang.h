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

	void visualise_trajectory(SDL_Renderer* renderer, Camera* camera);

private:
	float projectileSpeed = 800.0f;
	float visualRotation = 0.0f;
};