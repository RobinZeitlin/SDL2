#include "Player.h"

Player::Player()
{
	texture = textureManager->getTexture("player");
}

void Player::update()
{

}

void Player::render(SDL_Renderer* renderer)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };

	// 100 100 pos
	SDL_Rect destR = { 100, 100, 32, 32 };

	SDL_RenderCopy(renderer, texture, &srcR, &destR);

	std::cout << "Rendering " << texture << std::endl;
}