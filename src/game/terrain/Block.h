#pragma once

#include "../actors/Actor.h"

class Block : public Actor
{
public:
	Block();

	void render(SDL_Renderer* renderer) override;
};