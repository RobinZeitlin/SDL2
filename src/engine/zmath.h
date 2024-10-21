#pragma once

#include <cmath>
#include <glm.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace zmath
{
/**
 * @brief A collection of easing functions made by Robin Zeitlin.
 * @param t A value typically between 0 and 1, representing the time or progress.
 */

    inline float EaseOutElastic(float t) {
        const float c4 = (2 * M_PI) / 2.5f;

        if (t == 0) return 0;
        if (t == 1) return 1;

        return pow(2, -12 * t) * sin((t * 12 - 0.75f) * c4) + 1;
    }

    inline glm::vec2 EaseOutElastic(const glm::vec2& t)
    {
        return glm::vec2(EaseOutElastic(t.x), EaseOutElastic(t.x));
    }

    inline float EaseOutQuart(float t)
    {
        return 1.0f - pow(1.0f - t, 4);
    }

    inline glm::vec2 EaseOutQuart(const glm::vec2& t)
    {
        return glm::vec2(EaseOutQuart(t.x), EaseOutQuart(t.y));
    }

    inline float EaseOutCubicBounce(float x) {
        if (x < 0.5f) {
            // First half: scale up
            return 2 * pow(x * 2, 3) / 2;
        }
        else {
            // Second half: scale down
            return 2 * (1 - pow(2 * (x - 0.5f), 3)) / 2;
        }
    }
}