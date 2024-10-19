#pragma once

#include "Actor.h"

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
	}

	void update(float dt) {

		float distanceToPlayer = transform.get_distance(transform.position, game->player->transform.position);

		if (distanceToPlayer - 16 < proximityRange) {
			transform.position += (-transform.get_transform_up() * walkingSpeed) * dt;

			glm::vec2 direction = transform.get_direction_towards(transform.position, game->player->transform.position);

			float angle = std::atan2(direction.y, direction.x);

			transform.rotation.x = glm::degrees(angle);
		}
	}

	void render(SDL_Renderer* renderer, Camera* camera) override
	{
		SDL_Rect srcR = { 0, 0, 32, 32 };
		SDL_Rect destR = { (transform.position.x) - camera->x, (transform.position.y) - camera->y, 32, 32 };

		SDL_RenderCopyEx(renderer, texture, &srcR, &destR, transform.rotation.x, NULL, SDL_FLIP_NONE);
		
		float distanceToPlayer = transform.get_distance(transform.position, game->player->transform.position);

		if (distanceToPlayer - 16 > proximityRange)	{
			SDL_Color color = GIZMO_COLOR;
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			 
			const int numSegments = 20;
			const float increment = 2.0f * M_PI / numSegments;
			
			std::vector<SDL_FPoint> points;
			float angle = 0.0f;

			for (int i = 0; i < numSegments; i++) {
				float x = ((transform.position.x + transform.scale.x / 2) - camera->x + proximityRange * glm::cos(angle));
				float y = ((transform.position.y + transform.scale.y / 2) - camera->y + proximityRange * glm::sin(angle));
				
				SDL_FPoint newPos = { x, y };
				points.push_back(newPos);
			
				angle += increment;
			}

			points.push_back(points[0]);

			SDL_RenderDrawLinesF(renderer, points.data(), numSegments + 1);
			
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
	}

private:
	float walkingSpeed = 100;
	float proximityRange = 150;
};