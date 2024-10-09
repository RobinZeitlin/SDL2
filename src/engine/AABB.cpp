#include "AABB.h"
#include <iostream>

AABB AABB::from_position_size(Transform transform)
{
    glm::vec2 min = transform.position - transform.scale * 0.5f;
    glm::vec2 max = transform.position + transform.scale * 0.5f;

    return AABB(min, max);
}

bool aabb_overlap(AABB a, AABB b)
{
    bool overlap_x = a.max.x >= b.min.x && b.max.x >= a.min.x;
    bool overlap_y = a.max.y >= b.min.y && b.max.y >= a.min.y;

    return overlap_x && overlap_y;
}
