#pragma once

#include "Actor.h"

class Player : public Actor 
{
public:
	Player();
	~Player() {	};

	void update(float dt) override;
	void render(SDL_Renderer* renderer, Camera* camera) override;

	void check_overlap(float dt);

	void handleEvent(const SDL_Event& event);

	void shoot(Camera* camera);

private:
	bool isShooting;
};