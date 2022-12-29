#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"

class ColliderComponent : public Component
{
public:

	SDL_Rect collider;
	SDL_Rect grasses;
	std::string tag;

	SDL_Texture* tex;
	SDL_Texture* grass;
	SDL_Rect srcR, destR , gsrcR, gdestR;

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
		grasses.x = xpos;
		grasses.y = ypos;
		grasses.h = grasses.w = size;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		//grass = TextureManager::LoadTexture("grass.png");
		gsrcR = { 0,0,32,32 };
		gdestR = { grasses.x, grasses.y, grasses.w, grasses.h };
		//tex = TextureManager::LoadTexture("dirt.png");
		srcR = { 0,0,32,32 };
		destR = { collider.x, collider.y , collider.w, collider.h };

		
	}

	void update() override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;

			
		}
		if (tag != "encounter")
		{
			grasses.x = static_cast<int>(transform->position.x);
			grasses.y = static_cast<int>(transform->position.y);
			grasses.w = transform->width * transform->scale;
			grasses.h = transform->height * transform->scale;

			
		}
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;

		gdestR.x = grasses.x - Game::camera.x;
		gdestR.y = grasses.y - Game::camera.y;

	}

	void draw() override
	{
		

		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
		TextureManager::Draw(grass, gsrcR, gdestR, SDL_FLIP_NONE);

	}
};
