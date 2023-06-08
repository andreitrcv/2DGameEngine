#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"


class TankController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	Vector2D ProjectilePos;
	Vector2D ProjectileVel;
	float velProjX = 0.0f;
	float velProjY = -1.0f;


	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		ProjectileVel = Vector2D(velProjX, velProjY);
		ProjectilePos = Vector2D(transform->position.x + 48.0f, transform->position.y - 9.0f);		
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
                sprite->setRotation(0.0);
				ProjectileVel = Vector2D(0.0f, -3.0f);
				ProjectilePos = Vector2D(transform->position.x + 48.0f, transform->position.y - 9.0f);		
				break;
			case SDLK_a:
				transform->velocity.x = -1;
                sprite->setRotation(-90.0);
				ProjectileVel = Vector2D(-3.0f, 0.0f);
				ProjectilePos = Vector2D(transform->position.x - 42.0f, transform->position.y + 48.0f);		
				break;
			case SDLK_d:
				transform->velocity.x = 1;
                sprite->setRotation(90.0);
				ProjectileVel = Vector2D(3.0f, 0.0f);
				ProjectilePos = Vector2D(transform->position.x + 120.0f, transform->position.y + 48.0f);		
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->setRotation(180.0);
				ProjectileVel = Vector2D(0.0f, 3.0f);
				ProjectilePos = Vector2D(transform->position.x + 48.0f, transform->position.y + 120.0f);		
				break;
			case SDLK_SPACE:
				Game::assets->CreateProjectile(ProjectilePos, ProjectileVel, 250, 2, "projectile");
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
                sprite->setRotation(0.0);
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}

};