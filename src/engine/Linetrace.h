#pragma once

#include "LineHit.h"

class Linetrace {
public:
    LineHit line_trace(glm::vec2 startPos, glm::vec2 dir, std::vector<Collision_Channel> hitLayer, int rayLength = 200);
};

