#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

void GameObject::Update(int xx, int yy)
{
	
	

	srcRect.h = 600;
	srcRect.w = 600;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xx;
	destRect.y = yy; 
	destRect.w = 600 ; 
	destRect.h = 600;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

