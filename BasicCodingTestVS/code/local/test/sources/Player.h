#ifndef Player_HEADER
#define Player_HEADER

#include "Object.h"

#pragma once
class Player : public Object
{
protected:
	int level;
	int hp;
	int upgrades_left;
	bool canShoot;

public:
	Player();
	Player(Renderer::Color c, ObjectType ot);
};

#endif