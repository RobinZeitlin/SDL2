#include "Block.h"

#include "../../Game.h"

Block::Block()
{
	texture = textureManager->getTexture("cube");

	collision_channel = Collision_Channel::Ground;
	render_layer = Render_Layer::CollisionLayer;

	game->layers[static_cast<size_t>(render_layer)].push_back(this);
}

void Block::render(SDL_Renderer* renderer, Camera* camera)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };
	SDL_Rect destR = { (transform.position.x) - camera->x, (transform.position.y) - camera->y, 32, 32 };

	SDL_RenderCopy(renderer, texture, &srcR, &destR);
}
