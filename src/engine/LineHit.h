#pragma once

#include <glm.hpp>

#include "../game/actors/Actor.h"

class LineHit
{
public:
    Actor* hit_actor;
    glm::vec2 hit_point;
    glm::vec2 normal;
};