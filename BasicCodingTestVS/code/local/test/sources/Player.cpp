#include "Player.h"

Player::Player() :Object() {

}
Player::Player(Renderer::Color c, ObjectType ot) :
	Object(c, ot)
{
	canShoot = true;
	shootCooldown = false;
	hp = 5;
	score = 0;
	coins = 0;
	UpdateScoreBoard();
	AddHpObjects();
}
Player::Player(SDL_Renderer* rend, const char* assetPath, ObjectType ot) : Object(rend,assetPath,ot)
{
	canShoot = true;
	shootCooldown = false;
	hp = 5;
	score = 0;
	coins = 0;
	UpdateScoreBoard();
	AddHpObjects(rend);
}
void Player::AddHpObjects() {
	playerHpObjects = new vector<Object*>();
	for (int i = 0; i < hp; i++) {
		auto objectTemp = new Object(Renderer::BLUE, Object::PLAYER);
		objectTemp->SetSize(16, 16, false);
		objectTemp->SetPosition(16 + 16 * 2 * i, 872);//centered x, fixed y for now
		playerHpObjects->push_back(objectTemp);
	}
}
void Player::AddHpObjects(SDL_Renderer* rend) {
	playerHpObjects = new vector<Object*>();
	for (int i = 0; i < hp; i++) {
		auto objectTemp = new Object(rend, HpIconAsset, Object::UI_BUTTON);
		objectTemp->SetSize(16, 16, false);
		objectTemp->SetPosition(16+16*2*i , 872);//centered x, fixed y for now
		playerHpObjects->push_back(objectTemp);
	}
}
void Player::UpdateScore(int i) {
	score += i;
	UpdateScoreBoard();
}
void Player::AddCoins(int i) {
	coins += i;
	if (coins > 2000) {
		std::cout << "UPGRADE UNLOCKED !!!\n";
		level++;
		if (!canShoot) canShoot = true;
		coins -= 2000;
	}
	UpdateScoreBoard();
}
void Player::SetHp(int h) {
	hp = h;
	for (auto o : *playerHpObjects) {
		o->isActive = false;
	}
	for (int i = 0; i < hp; i++) {
		playerHpObjects->at(i)->isActive = true;
	}
}
int Player::GetHp() {
	return hp;
}

void Player::UpdateScoreBoard(){
	std::cout <<"HP : "<< hp<< " | Score : " << score  << " | Coins : " << coins << std::endl;
}