#include "Spline.h"

#include "../../Game.h"

void Spline::render_debug(SDL_Renderer* renderer)
{
    glm::vec2 lastPoint = glm::vec2(0);

    for (auto point : splinePoints) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        if (lastPoint != glm::vec2(0)) {
            SDL_RenderDrawLineF(renderer,
                lastPoint.x - game->camera->x,
                lastPoint.y - game->camera->y,
                point.x - game->camera->x,
                point.y - game->camera->y);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        DebugDraw::draw_debug_sphere(renderer, glm::vec2(
                point.x - game->camera->x,
                point.y - game->camera->y), 
                10, 10);

        lastPoint = point;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
