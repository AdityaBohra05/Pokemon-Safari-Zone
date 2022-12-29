#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"





class KeyboardController : public Component
{
public:

	int side;

	TransformComponent* transform;
	SpriteComponent* sprite;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		transform->run.x = 0;
		
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				transform->tp.y = -1;
				if (true) {
					sprite->Play("Walk_Up");
				}
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				transform->tp.x = -1;
				if (true) {
					sprite->Play("Walk_Side");
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				}
				
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				transform->tp.x = 1;
				if (true) {
					sprite->Play("Walk_Side");
					if (side == 1)
					{
						sprite->spriteFlip = SDL_FLIP_NONE;
						side = 0;
					}
				}
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				transform->tp.y = 1;
				if (true) {
					sprite->Play("Walk_Down");
					


				}
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				
					sprite->Play("Idle_Up");
				
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				
					sprite->Play("Idle_Side");
					
					side= 1;
			
				
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				
					sprite->Play("Idle_Side");
				
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				
					sprite->Play("Idle_Down");
				
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
			
		}
	}
};