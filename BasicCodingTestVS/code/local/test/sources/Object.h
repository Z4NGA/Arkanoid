#ifndef Object_HEADER
#define Object_HEADER


#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "renderer.hpp"
#include "GameEvent.h"
#include <iostream>
#pragma once
/*
* @class: base class for all game objects
*/
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
	~Object();
	/*
	* @brief: changes the objects texture to a new texture loaded from the given assetPath
	*/
	void ChangeTexture(SDL_Renderer* rend, const char* assetPath);
	/*
	* @brief: sets the objects size, if fixedsize is not specified, the object will be at a fixed size of 16*16
	*/
	void SetSize(int w, int h,bool fixedSize=true);
	/*
	* @brief: sets an objects position on the screen
	*/
	void SetPosition(int x, int y);
	/*
	* @brief: moves the object with x on the xAxis and y on theYaxis
	*/
	void Move(int x, int y);
	/*
	* @brief: moves the object depending on the game event given
	*/
	void Move(GameEvent e);
	/*
	* @brief: draws an object on the screen, can be overriden for inhereting classes
	*/
	void DrawObject(SDL_Renderer* rend);
	/*
	* @brief: sets the velocity of an object which causes constant movement
	*/
	void SetVelocity(int x, int y);
};

#endif