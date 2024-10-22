#pragma once

#include "Actor.h"

class Boomerang : public Actor
{
public:
	Boomerang();

	void update(float dt);

	void render(SDL_Renderer* renderer, Camera* camera) override;

	void check_overlap();

private:
	float projectileSpeed = 500.0f;
	float visualRotation = 0.0f;
};