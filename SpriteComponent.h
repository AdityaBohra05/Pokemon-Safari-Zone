#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}

	SpriteComponent(const char* path , bool isAnimated )
	{
		animated = isAnimated;

		Animation idle_down = Animation(0, 1, 100);
		Animation walk_down = Animation(2, 3, 200);
		Animation idle_up = Animation(5, 1, 100);
		Animation walk_up = Animation(4, 3, 200);
		Animation idle_side = Animation(1, 1, 100);
		Animation walk_side = Animation(3, 3, 200);

		animations.emplace("Idle_Down", idle_down);
		animations.emplace("Walk_Down", walk_down);
		animations.emplace("Idle_Up", idle_up);
		animations.emplace("Walk_Up", walk_up);
		animations.emplace("Idle_Side", idle_side);
		animations.emplace("Walk_Side", walk_side);

		Play("Idle_Down");
		setTex(path);
	}


	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		//destRect.w = destRect.h = 32;
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;


		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};