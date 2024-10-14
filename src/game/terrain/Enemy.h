#pragma once

#include "../actors/Actor.h"

class Camera;

class Enemy : public Actor
{
public:
	Enemy()
	{
		texture = textureManager->getTexture("enemy");
		collision_channel = Collision_Channel::Enemy;
	}

	void render(SDL_Renderer* renderer, Camera* camera) override
	{
		SDL_Rect srcR = { 0, 0, 32, 32 };
		SDL_Rect destR = { (transform.position.x) - camera->x, (transform.position.y) - camera->y, 32, 32 };

		SDL_RenderCopy(renderer, texture, &srcR, &destR);
	}
};