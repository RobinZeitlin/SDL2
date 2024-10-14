#pragma once

#include "Block.h"

class Camera;

class GrassBlock : public Block
{
public:
	GrassBlock() 
	{
		texture = textureManager->getTexture("grass");
		collision_channel = Collision_Channel::Ground;
	}

	void render(SDL_Renderer* renderer, Camera* camera) override 
	{
		SDL_Rect srcR = { 0, 0, 32, 32 };
		SDL_Rect destR = { (transform.position.x) - camera->x, (transform.position.y) - camera->y, 32, 32 };

		SDL_RenderCopy(renderer, texture, &srcR, &destR);
	}
};