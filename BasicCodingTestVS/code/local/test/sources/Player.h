#ifndef Player_HEADER
#define Player_HEADER

#include "Object.h"

#pragma once
class Player : public Object
{
public:
	Player();
	Player(Renderer::Color c, ObjectType ot);
};

#endif