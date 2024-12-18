#include "Player.h"
#include "../../Game.h"
#include "../actors/Projectile.h"
#include "../../engine/ParticleController.h"
#include "../../engine/AABB.h"

#include "../../engine/zmath.h"

Player::Player(glm::vec2 startPos)
{
	texture = textureManager->getTexture("player");

    collision_channel = Collision_Channel::Player;
    render_layer = Render_Layer::Entities;

    actorName = "Player";

    transform.position = startPos;

    weapon = nullptr;

    game->layers[static_cast<size_t>(render_layer)].push_back(this);

    auto boomerang = new Boomerang();
    game->spawnActor(boomerang, glm::vec2(startPos));
}

void Player::update(float dt)
{
    set_weapon_pos();

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

    glm::vec2 direction = worldSpaceMousePos - transform.position;
    if (glm::length(direction) > 0.0f) {
        direction = glm::normalize(direction);
    }
    else {
        direction = glm::vec2(0.0f, 0.0f);
    }
 
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

    if (game->spline != nullptr)
        check_for_spline_attachment(dt);
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
void Player::check_for_spline_attachment(float dt) {

    glm::vec2 globalPlayerPos = transform.position;
    glm::vec2 positionOnSpline = game->spline->get_closest_point_on_spline(globalPlayerPos);

    float range = 150.0f;
    float dist = zmath::get_distance(globalPlayerPos, positionOnSpline);
    if (dist < range) {
        game->camera->updateCamera(positionOnSpline, dt);
    } else
    {
        game->camera->updateCamera(transform.position, dt);
    }
        
}

void Player::shoot(Camera* camera)
{
    float offsetPos = 50.0f;

    glm::vec2 direction = glm::normalize(transform.get_transform_up());
    glm::vec2 crtPos = transform.position + direction * offsetPos;

    if (weapon != nullptr)
    {
        weapon->launch_boomerang(direction, 800.0f);
        weapon = nullptr;
    }
}

void Player::set_weapon_pos()
{
    glm::vec2 handPos = transform.position + (transform.get_transform_right() * glm::vec2(10));
    glm::vec2 dir = glm::normalize(transform.get_transform_up());

    float angleInDegrees = glm::degrees(atan2(dir.y, dir.x));
    float handRotationOffset = 240.0f;

    if (weapon != nullptr) {
        weapon->transform.position = handPos;
        weapon->visualRotation = angleInDegrees + handRotationOffset;
    }
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