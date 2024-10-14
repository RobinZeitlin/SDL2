#include "Player.h"
#include "../../Game.h"

Player::Player()
{
	texture = textureManager->getTexture("player");
	transform.position.x = 100;
	transform.position.y = 100;

    collision_channel = Collision_Channel::Player;

    actorName = "Player";
}

void Player::update()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    if (currentKeyStates[SDL_SCANCODE_W])
    {
        transform.position.y -= 0.1f;
    }
    if (currentKeyStates[SDL_SCANCODE_S])
    {
        transform.position.y += 0.1f;
    }
    if (currentKeyStates[SDL_SCANCODE_A])
    {
        transform.position.x -= 0.1f;
    }
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        transform.position.x += 0.1f;
    }

    check_overlap();
}

void Player::render(SDL_Renderer* renderer, Camera* camera)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };

	SDL_Rect destR = { transform.position.x - camera->x, transform.position.y - camera->y, 32, 32 };

	SDL_RenderCopy(renderer, texture, &srcR, &destR);
}

void Player::check_overlap()
{
    glm::vec2 previous_position = transform.position;

    Actor* hit_actor = game->get_overlapping_actor(this, Collision_Channel::Ground);
    if (hit_actor != nullptr)
    {
        glm::vec2 direction_to_actor = transform.position - hit_actor->transform.position;
        glm::vec2 collision_normal = glm::normalize(direction_to_actor);

        transform.position = previous_position + collision_normal * 0.15f;
    }
}