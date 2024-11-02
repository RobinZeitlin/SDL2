#include "SplinePoint.h"

#include "../../Game.h"

void SplinePoint::render_point()
{
	auto renderer = game->renderer;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

	DebugDraw::draw_debug_sphere(renderer, glm::vec2(
		pos.x - game->camera->x,
		pos.y - game->camera->y),
		10, 10);

	render_handle(renderer);
}

void SplinePoint::render_handle(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

	SDL_RenderDrawLineF(renderer,
		pos.x - game->camera->x,
		pos.y - game->camera->y,
		pos.x - game->camera->x,
		pos.y - game->camera->y - 50);

	SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);

	DebugDraw::draw_debug_sphere(renderer, glm::vec2(
		pos.x - game->camera->x,
		pos.y - game->camera->y - 50),
		5, 10);
}
