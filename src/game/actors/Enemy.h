#pragma once

#include "Actor.h"
#include "../../engine/DebugDraw.h"

#include <queue>

class Camera;

class Enemy : public Actor
{
public:
	Enemy()
	{
		texture = textureManager->getTexture("enemy");

		collision_channel = Collision_Channel::Enemy;
		render_layer = Render_Layer::Entities;

		game->layers[static_cast<size_t>(render_layer)].push_back(this);

		pathPositions = game->pathFindingManager->get_path_from_to(transform.position / glm::vec2(32), glm::vec2(0));

		std::cout << "Initialized pathPositions size: " << pathPositions.size() << std::endl;
	}

	void update(float dt) {
		std::cout << "Current pathPositions size: " << pathPositions.size() << std::endl;

		if (game->bEditor) return;

		float distanceToPlayer = transform.get_distance(transform.position, game->player->transform.position);

		if (distanceToPlayer - 16 < proximityRange && pathPositions.size() > 0) {
			transform.position += (-transform.get_transform_up() * walkingSpeed) * dt;

			glm::vec2 direction = transform.get_direction_towards(transform.position, pathPositions.back());

			float angle = std::atan2(direction.y, direction.x);

			transform.rotation.x = glm::degrees(angle);
		}

		check_overlap();
	}

	void render(SDL_Renderer* renderer, Camera* camera) override
	{
		SDL_Rect srcR = { 0, 0, 32, 32 };
		SDL_Rect destR = { (transform.position.x) - camera->x, (transform.position.y) - camera->y, 32, 32 };

		SDL_RenderCopyEx(renderer, texture, &srcR, &destR, transform.rotation.x, NULL, SDL_FLIP_NONE);

		float distanceToPlayer;

		if (!game->bEditor)
			distanceToPlayer = transform.get_distance(transform.position, game->player->transform.position);
		else
			distanceToPlayer = 100.0f;

		if (distanceToPlayer - 16 > proximityRange)	{
			SDL_Color color = GIZMO_COLOR;

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

			DebugDraw::draw_debug_sphere(renderer, glm::vec2(
				((transform.position.x + transform.scale.x / 2) - camera->x), 
				((transform.position.y + transform.scale.y / 2) - camera->y)), 
				proximityRange, 20);

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
	}

	void check_overlap()
	{
		Actor* hit_actor = game->get_overlapping_actor(this, Collision_Channel::P_Projectile);
		if (hit_actor != nullptr)
		{
			auto particleCtrl = new ParticleController(transform.position, textureManager->getTexture("enemy"), 30, 12, 200, 0.5f);
			game->particleControllers.push_back(particleCtrl);

			auto particleCtrl2 = new ParticleController(transform.position, textureManager->getTexture("effectred"), 1, 100, 0, 0.5f);
			game->particleControllers.push_back(particleCtrl2);
			destroy();
		}
	};

private:
	float walkingSpeed = 250;
	float proximityRange = 250;

	std::queue<glm::vec2> pathPositions;
};