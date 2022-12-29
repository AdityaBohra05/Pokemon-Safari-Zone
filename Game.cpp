#include "Game.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include <time.h>
#include <iostream>




GameObject* mop;
GameObject* moa;
GameObject* mob;
GameObject* moc;
GameObject* mod;
GameObject* fled;
GameObject* caught;

int cmop;
Map* map;




SDL_Renderer* Game::renderer = nullptr;

Manager manager;

SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,224,224 };



bool Game::isRunning = false;

auto& player(manager.addEntity());







Game::Game()
{}
Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{


	


	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window)
		{
			std::cout << "window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}

	else
	{
		isRunning = false;
	}
	mop = new GameObject("Lapras.png", 0, 600);
	moa = new GameObject("Venusaur.png", 0, 600);
	mob = new GameObject("Pikachu.png", 0, 600);
	moc = new GameObject("Gengar.png", 0, 600);
	mod = new GameObject("Dragonite.png", 0, 600);
    fled = new GameObject("fled.png", 0, 600);
	caught = new GameObject("caught.png", 0, 600);

	
	map = new Map("MAP_ss.png", 2, 32);

	

	map->LoadMap("MapPokemon.map", 14, 14);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("walkfull.png" , true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& grasses(manager.getGroup(Game::groupGrass));


void Game::handleEvents()
{
	

	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
         
		default:
			break;
	}

}

void Game::update()
{  

	
	

	
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D lol = player.getComponent<TransformComponent>().lol;

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			
			player.getComponent<TransformComponent>().position = playerPos;
		}
		
		
	}

	srand(time(0));
	int tot = (rand() %5) + 1;
	int pop = (rand() %9) + 2;
	int prob = (rand() % 9) + 1;
	
	

	int z = (rand() % 6);
	

	if (tot == pop)
	{
		for (auto& g : grasses)
		{
			
			SDL_Rect cCol = g->getComponent<ColliderComponent>().grasses;
			if (Collision::AABB(cCol, playerCol))
			{

				cmop = 1;
				
				
				if (z == 1)
				{
					mop->Update(0, 0);
					
					player.getComponent<TransformComponent>().position = lol; //playerPos;
				}
				if (z == 2)
				{
					moa->Update(0, 0);
					
					player.getComponent<TransformComponent>().position = lol; //playerPos;
				}
				if (z == 3)
				{
					mob->Update(0, 0);
					
					player.getComponent<TransformComponent>().position = lol; //playerPos;
				}
				if (z == 4)
				{
					moc->Update(0, 0);
					
					player.getComponent<TransformComponent>().position = lol; //playerPos;
				}

				if (z == 5)
				{
					mod->Update(0, 0);
					
					player.getComponent<TransformComponent>().position = lol; //playerPos;
				}

				
			}


		}
	}
	

	

	

	camera.x = player.getComponent<TransformComponent>().position.x - 300;
	camera.y = player.getComponent<TransformComponent>().position.y - 300;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;

	

	


	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_r:
			if (cmop == 1);
			{
				mop->Update(0, 600);
				moa->Update(0, 600);
				mob->Update(0, 600);
				moc->Update(0, 600);
				mod->Update(0, 600);
				fled->Update(0, 600);
				caught->Update(0, 600);
				cmop = 0;
			}

			break;
		case SDLK_c:
			if(prob%2 == 0)
			fled->Update(0, 0);

			if (prob % 2 != 0)
			caught->Update(0, 0);
			break;
		default:
			break;
		}
	}
	
	
}


void Game::render()
{
	
	SDL_RenderClear(renderer);
	
	

	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
		
	}
	for (auto& g : grasses)
	{
		g->draw();

	}

	for (auto& p : players)
	{
		p->draw();
	}

	if (cmop == 1)
	{	
		mop->Render();
		moa->Render();
		mob->Render();
		moc->Render();
		mod->Render();
		fled->Render();
		caught->Render();
		
	}
	
	SDL_RenderPresent(renderer);
	

}

void Game::clean()
{


	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game Cleaned" << std::endl;
}
