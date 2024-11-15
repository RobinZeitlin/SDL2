#include "Boomerang.h"
#include "../../Game.h"
#include "../../engine/DebugDraw.h"
#include "../../engine/Linetrace.h"
#include "../../engine/LineHit.h"

Boomerang::Boomerang()
{
	texture = textureManager->getTexture("boomerang");

	collision_channel = Collision_Channel::P_Projectile;
	render_layer = Render_Layer::Entities;

	game->layers[static_cast<size_t>(render_layer)].push_back(this);
}

void Boomerang::update(float dt)
{
	transform.position += (transform.get_transform_up() * projectileSpeed) * dt;

	visualRotation += projectileSpeed * dt;

	check_overlap();

	if (projectileSpeed >= 0)
		projectileSpeed -= 200.0f * dt;
	else
		projectileSpeed = 0.0f;
}

void Boomerang::render(SDL_Renderer* renderer, Camera* camera)
{
	//visualise_trajectory(renderer, camera);

	SDL_Rect srcR = { 0, 0, 32, 32 };

	SDL_Rect destR = { transform.position.x - camera->x, transform.position.y - camera->y, 36, 36 };

	SDL_RenderCopyEx(renderer, texture, &srcR, &destR, visualRotation, NULL, SDL_FLIP_NONE);

}

void Boomerang::check_overlap()
{
	if (game->player->weapon != nullptr) return;

	Actor* hit_ground_actor = game->get_overlapping_actor(this, Collision_Channel::Ground);
	if (hit_ground_actor != nullptr)
	{
		auto particleCtrl = std::make_unique<ParticleController>(transform.position + (transform.scale * 0.5f), textureManager->getTexture("effect2"), 30, 25, 250, 0.25f);
		game->spawn_particle_system(std::move(particleCtrl));

		auto particleCtrl2 = std::make_unique<ParticleController>(transform.position + (transform.scale * 0.5f), textureManager->getTexture("effect"), 1, 80, 0, 0.5f);
		game->spawn_particle_system(std::move(particleCtrl2));

		transform.rotation.x = getBounceDir();
		
		projectileSpeed += 10;
	}

	Actor* hit_player_actor = game->get_overlapping_actor(this, Collision_Channel::Player);
	if (hit_player_actor != nullptr)
	{
		game->player->pick_up(this);
	}
}

float Boomerang::getBounceDir()
{
	glm::vec2 origin = transform.position;
	glm::vec2 dir = transform.get_transform_up();
	
	Linetrace linetrace;
	LineHit result = linetrace.line_trace(origin, dir, { Collision_Channel::Ground } , 200);
	
	if (result.hit_point != origin) {
	    if (result.hit_actor != nullptr) {
	        // reflected ray calculation
	        glm::vec2 incoming_ray = glm::normalize(result.hit_point - origin);
	        glm::vec2 reflection = incoming_ray - result.normal * (2.0f * glm::dot(incoming_ray, result.normal));
	
	        dir = reflection;
	        origin = result.hit_point;

			float angle = glm::degrees(atan2(dir.y, dir.x));
			if (angle < 0) {
				angle += 360;
			}

			return angle;
	    }
	}
	return 0;
}

void Boomerang::visualise_trajectory(SDL_Renderer* renderer, Camera* camera)
{
    SDL_SetRenderDrawColor(renderer, 255, 120, 0, 255);

    glm::vec2 origin = transform.position;
    glm::vec2 dir = transform.get_transform_up();

    Linetrace linetrace;
	LineHit result = linetrace.line_trace(origin, dir, { Collision_Channel::Ground }, 1000);

    if (result.hit_point != origin) {

        SDL_RenderDrawLine(renderer, origin.x - camera->x + 16, origin.y - camera->y + 16,
            result.hit_point.x - camera->x + 16, result.hit_point.y - camera->y + 16);

        if (result.hit_actor != nullptr) {

            glm::vec2 normal_start = result.hit_point;
            glm::vec2 normal_end = normal_start - result.normal * 50.0f;

            // draw the normal
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(renderer,
                normal_start.x - camera->x + 16,
                normal_start.y - camera->y + 16,
                normal_end.x - camera->x + 16,
                normal_end.y - camera->y + 16);

            // reflected ray calculation
            glm::vec2 incoming_ray = glm::normalize(result.hit_point - origin);
            glm::vec2 reflection = incoming_ray - result.normal * (2.0f * glm::dot(incoming_ray, result.normal));
            glm::vec2 reflection_end = result.hit_point + reflection * 500.0f;

            // draw ray
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer,
                result.hit_point.x - camera->x + 16,
                result.hit_point.y - camera->y + 16,
                reflection_end.x - camera->x + 16,
                reflection_end.y - camera->y + 16);
        }
    }

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Boomerang::launch_boomerang(glm::vec2 dir, float speed)
{
	float angleInDegrees = glm::degrees(atan2(dir.y, dir.x));

	projectileSpeed = speed;
	transform.rotation.x = angleInDegrees;
	transform.position += dir * 50.0f;
}
