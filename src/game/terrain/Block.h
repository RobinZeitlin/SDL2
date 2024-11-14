#pragma once

#include "../actors/Actor.h"

class Camera;

class Block : public Actor
{
public:
	Block();

	void render(SDL_Renderer* renderer, Camera* camera) override;
};