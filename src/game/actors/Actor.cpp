#include "Actor.h"

Actor::Actor() : texture(nullptr) {}

Actor::~Actor() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
