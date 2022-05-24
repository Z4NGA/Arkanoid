#ifndef Object_HEADER
#define Object_HEADER


#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "renderer.hpp"
#include "GameEvent.h"
#include <iostream>
#pragma once
class Object
{
public:
	const int fixedSize = 16;
	enum ObjectSize {
		SMALL,
		MEDIUM,
		BIG
	};
	enum ObjectType {
		PLAYER,
		BOMB,
		BOX,
		Empty,
		BOOST,
		BALL,
		UI_BUTTON,
		BULLET,
	};
	enum RenderType {
		COLOR,
		TEXTURE
	};
	bool isActive;
	RenderType renderType;
	int VelocityX, VelocityY;
	bool isMoving;
	SDL_Rect transform;
	Renderer::Color color;
	SDL_Texture* texture;
	ObjectType type;
	Object();
	Object(Renderer::Color c, ObjectType ot);
	Object(SDL_Renderer* rend, const char* assetPath, ObjectType ot);
	void ChangeTexture(SDL_Renderer* rend, const char* assetPath);
	~Object();
	void SetSize(int w, int h,bool fixedSize=true);
	void SetPosition(int x, int y);
	void Move(int x, int y);
	void Move(GameEvent e);
	void DrawObject(SDL_Renderer* rend);
	void SetVelocity(int x, int y);
};

#endif