#ifndef Player_HEADER
#define Player_HEADER

#include "Object.h"
#include <iostream>
#include <vector>
#pragma once
using namespace std;
/*
* @class: player class that controls the player pad and object
*/
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
	/*
	* @brief: increases the player score with the i value, default is 5
	*/
	void UpdateScore(int i = 5);
	/*
	* @brief: add coins to the player, default is 50
	*/
	void AddCoins(int i = 50);
	/*
	* @brief: sets the player's hp
	*/
	void SetHp(int hp);
	/*
	* @return: returns the player hp
	*/
	int GetHp();
	/*
	* @brief: updates the score and hp board
	*/
	void UpdateScoreBoard();
	/*
	* @brief: sets the initial ui hp objects, that indicates the players hp, uses colors
	*/
	void AddHpObjects();
	/*
	* @brief: sets the initial ui hp objects, that indicates the players hp, uses textures
	*/
	void AddHpObjects(SDL_Renderer* rend);
};

#endif