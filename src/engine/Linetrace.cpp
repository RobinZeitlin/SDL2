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

                glm::vec2 hit_point_offset = (linehit.hit_point - linehit.hit_actor->transform.position);

                if (fabs(hit_point_offset.x) > fabs(hit_point_offset.y)) {
                    // left or right
                    linehit.normal = (hit_point_offset.x > 0) ? glm::vec2(-1, 0) : glm::vec2(1, 0);
                }
                else {
                    // top or bottom
                    linehit.normal = (hit_point_offset.y > 0) ? glm::vec2(0, -1) : glm::vec2(0, 1);
                }

                return linehit;
            }
        }
    }

    glm::vec2 endPoint = startPos + dir * static_cast<float>(rayLength);

    linehit.hit_point = endPoint;
    linehit.hit_actor = nullptr;

    return linehit;
}