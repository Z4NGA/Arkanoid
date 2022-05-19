#ifndef Player_HEADER
#define Player_HEADER

#include "Object.h"
#include <iostream>
#pragma once
class Player : public Object
{
protected:
	int level;
	int hp;
	int upgrades_left;
	bool canShoot;
	int score;
	int coins;

public:
	Player();
	Player(Renderer::Color c, ObjectType ot);
	void UpdateScore(int i = 5);
	void AddCoins(int i = 50);
	void SetHp(int hp);
	int GetHp();
};

#endif