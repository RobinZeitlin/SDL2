#pragma once

#include "Actor.h"

class Player : public Actor 
{
public:
	Player();
	~Player() {	};

	void update() override;
	void render(SDL_Renderer* renderer) override;
};