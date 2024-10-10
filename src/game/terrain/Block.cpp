#include "Block.h"

Block::Block()
{
	texture = textureManager->getTexture("dirt");

	collision_channel = Collision_Channel::Ground;
}

void Block::render(SDL_Renderer* renderer, Camera* camera)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };

	SDL_Rect destR = { (transform.position.x) - camera->x, (transform.position.y) - camera->y, 32, 32 };

	SDL_RenderCopy(renderer, texture, &srcR, &destR);
}
