#ifndef Player_HEADER
#define Player_HEADER

#include "Object.h"
#include <iostream>
#include <vector>
#pragma once
using namespace std;
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
	const char* HpIconAsset = "Assets/hp_icon.png";
	vector<Object*>* playerHpObjects;
	bool shootCooldown;
	Player();
	Player(SDL_Renderer* rend, const char* assetPath, ObjectType ot);
	Player(Renderer::Color c, ObjectType ot);
	void UpdateScore(int i = 5);
	void AddCoins(int i = 50);
	void SetHp(int hp);
	int GetHp();
	void UpdateScoreBoard();
	void AddHpObjects();
	void AddHpObjects(SDL_Renderer* rend);
};

#endif