#include "Spline.h"

#include "../../Game.h"

void Spline::render_debug(SDL_Renderer* renderer)
{
    glm::vec2 lastPoint = glm::vec2(0);

    for (auto point : splinePoints) {
        point->render_point();

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

        if (lastPoint != glm::vec2(0)) {
            SDL_RenderDrawLineF(renderer,
                lastPoint.x - game->camera->x,
                lastPoint.y - game->camera->y,
                point->transform.position.x - game->camera->x,
                point->transform.position.y - game->camera->y);
        }

        lastPoint = point->transform.position;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}