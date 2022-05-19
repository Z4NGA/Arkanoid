#ifndef Object_HEADER
#define Object_HEADER


#include "SDL2/SDL.h"
#include "renderer.hpp"
#include "GameEvent.h"
#include <iostream>
#pragma once
class Object
{
public:
	const int fixedSize = 25;
	enum ObjectType {
		PLAYER,
		ENEMY,
		BOX,
		Empty,
		UI_BUTTON,
	};
	SDL_Rect transform;
	Renderer::Color color;
	ObjectType type;
	Object();
	Object(Renderer::Color c, ObjectType ot);
	~Object();
	void SetSize(int w, int h);
	void SetPosition(int x, int y);
	void Move(int x, int y);
	void Move(GameEvent e);
	void DrawObject(SDL_Renderer* rend);
};

#endif