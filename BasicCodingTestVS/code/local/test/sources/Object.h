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
		BOMB,
		BOX,
		Empty,
		BOOST,
		BALL,
		UI_BUTTON,
	};
	int VelocityX, VelocityY;
	bool isMoving;
	SDL_Rect transform;
	Renderer::Color color;
	ObjectType type;
	Object();
	Object(Renderer::Color c, ObjectType ot);
	~Object();
	void SetSize(int w, int h,bool fixedSize=true);
	void SetPosition(int x, int y);
	void Move(int x, int y);
	void Move(GameEvent e);
	void DrawObject(SDL_Renderer* rend);
	void SetVelocity(int x, int y);
};

#endif