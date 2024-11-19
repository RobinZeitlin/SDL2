#pragma once

#include "Actor.h"
#include "Boomerang.h"

class Player : public Actor 
{
public:
	Player(glm::vec2 startPos);
	~Player() {	};

	void update(float dt) override;
	void render(SDL_Renderer* renderer, Camera* camera) override;

	void check_overlap(float dt);
	void check_for_spline_attachment(float dt);

	void set_weapon_pos();

	void shoot(Camera* camera);

	bool pick_up(Boomerang* boomerang) { 
		if (weapon == nullptr) {
			weapon = boomerang;
			weapon->projectileSpeed = 0.0f;
			return true;
		}
		return false;
	}

	// expand this with a weapon class instead.
	Boomerang* weapon;

private:
	bool isShooting;

	float handRotationOffset;
};