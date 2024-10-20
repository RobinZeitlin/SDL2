#include "Player.h"
#include "../../Game.h"
#include "../actors/Projectile.h"

Player::Player()
{
	texture = textureManager->getTexture("player");

    collision_channel = Collision_Channel::Player;
    render_layer = Render_Layer::Entities;

    actorName = "Player";

    game->layers[static_cast<size_t>(render_layer)].push_back(this);
}

void Player::update(float dt)
{
    const float playerSpeed = 350.0f;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    if (currentKeyStates[SDL_SCANCODE_W]) {
        transform.position.y -= playerSpeed * dt;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        transform.position.y += playerSpeed * dt;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        transform.position.x -= playerSpeed * dt;
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        transform.position.x += playerSpeed * dt;
    }

    // rotate player towards the mouse position

    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    glm::vec2 worldSpaceMousePos;

    worldSpaceMousePos.x = mouseX + game->camera->x;
    worldSpaceMousePos.y = mouseY + game->camera->y;

    glm::vec2 direction = glm::normalize(worldSpaceMousePos - transform.position);
 
    float angle = std::atan2(direction.y, direction.x);

    transform.rotation.x = glm::degrees(angle);

    check_overlap(dt);

    if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if (!isShooting) {
            shoot(game->camera);
            isShooting = true; 
        }
    }
    else {
        isShooting = false;
    }
}

void Player::render(SDL_Renderer* renderer, Camera* camera)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };

	SDL_Rect destR = { transform.position.x - camera->x, transform.position.y - camera->y, 32, 32 };

	SDL_RenderCopyEx(renderer, texture, &srcR, &destR, transform.rotation.x, NULL, SDL_FLIP_NONE);

    // gizmos

    const int gizmoMultiplier = 50;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    glm::vec2 upVector = glm::vec2(transform.position.x + transform.get_transform_up().x * gizmoMultiplier, transform.position.y + transform.get_transform_up().y * gizmoMultiplier);
    SDL_RenderDrawLine(renderer,transform.position.x - camera->x + 16, transform.position.y - camera->y + 16, upVector.x - camera->x + 16, upVector.y - camera->y + 16);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    glm::vec2 rightVector = glm::vec2(transform.position.x + transform.get_transform_right().x * gizmoMultiplier, transform.position.y + transform.get_transform_right().y * gizmoMultiplier);
    SDL_RenderDrawLine(renderer, transform.position.x - camera->x + 16, transform.position.y - camera->y + 16, rightVector.x - camera->x + 16, rightVector.y - camera->y + 16);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Player::shoot(Camera* camera)
{
    const float offsetPos = 50;
    auto projectile = new Projectile();

    glm::vec2 direction = transform.get_transform_up();
    glm::vec2 spawnPos = transform.position + direction * offsetPos;

    game->spawnActor(projectile, spawnPos, transform.rotation);
}

void Player::check_overlap(float dt)
{
    glm::vec2 previous_position = transform.position;

    Actor* hit_ground_actor = game->get_overlapping_actor(this, Collision_Channel::Ground);
    if (hit_ground_actor != nullptr)
    {
        glm::vec2 direction_to_actor = transform.position - hit_ground_actor->transform.position;
        glm::vec2 collision_normal = glm::normalize(direction_to_actor);

        transform.position = previous_position + collision_normal * 500.0f * dt;
    }

    Actor* hit_enemy_actor = game->get_overlapping_actor(this, Collision_Channel::Enemy);
    if (hit_enemy_actor != nullptr)
    {
        destroy();
    }
}