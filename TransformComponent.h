#pragma once
#include "Game.h"
#include "ECS.h"
#include"Components.h"
#include"Vector2D.h"




class TransformComponent : public Component
{
public:

	
	
	Vector2D position;
	Vector2D velocity;
	Vector2D tp;
	Vector2D dog;
	Vector2D cat;
	Vector2D lol;
	Vector2D run;
	
	
	

	int height = 32;
	int width = 32;
	int scale = 1;
	
	int speed = 1;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.x = 210;
		position.y = 450;
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.Zero();
	}

	TransformComponent(bool apple)
	{

		

		height = 600;
		width = 600;
		
		scale = 1;

		position.x = 0;
		position.y = 0;
		
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;

	}

	void init() override
	{
		velocity.Zero();
	}
	void update() override
	{

		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		lol.x = 210;
		lol.y = 450;
		
			
		
	}

	
};