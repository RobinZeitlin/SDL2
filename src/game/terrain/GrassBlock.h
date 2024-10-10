#pragma once

#include "Block.h"

class Camera;

class GrassBlock : public Block
{
public:
	GrassBlock();

	void render(SDL_Renderer* renderer, Camera* camera) override;
};