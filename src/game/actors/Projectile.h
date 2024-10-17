#pragma once

#include "Actor.h"

class Projectile : public Actor
{
public:
	Projectile();
	~Projectile() {	};

	void update(float dt) override;
	void render(SDL_Renderer* renderer, Camera* camera) override;

	void check_overlap();

private:
	float projectileSpeed;
};