#include "Linetrace.h"
#include "../Game.h"
#include "SDL.h"
#include "AABB.h"
#include "glm.hpp"

LineHit Linetrace::line_trace(glm::vec2 startPos, glm::vec2 dir, Collision_Channel hitLayer, int rayLength)
{
    LineHit linehit;

    glm::vec2 lastImpactPoint = startPos;

    for (int i = 0; i < rayLength; i++) {
        glm::vec2 upVector = startPos + dir * static_cast<float>(i);

        for (int j = 0; j < MAX_ACTORS; j++) {
            if (game->actorList[j] == nullptr || game->actorList[j]->collision_channel != hitLayer) continue;

            AABB actorAABB = AABB::from_position_size(game->actorList[j]->transform);

            bool overlap = (upVector.x >= actorAABB.min.x && upVector.x <= actorAABB.max.x &&
                upVector.y >= actorAABB.min.y && upVector.y <= actorAABB.max.y);

            if (overlap) {
                lastImpactPoint = upVector;

                linehit.hit_point = lastImpactPoint;
                linehit.hit_actor = game->actorList[j];

                return linehit;
            }
        }
    }

    glm::vec2 endPoint = startPos + dir * static_cast<float>(rayLength);

    linehit.hit_point = endPoint;
    linehit.hit_actor = nullptr;

    return linehit;
}