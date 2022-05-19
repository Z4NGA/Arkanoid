#include "Player.h"

Player::Player() :Object() {

}
Player::Player(Renderer::Color c, ObjectType ot) :
	Object(c, ot)
{
	shootCooldown = false;
	hp = 5;
	score = 0;
	coins = 0;
	UpdateScoreBoard();
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
}
int Player::GetHp() {
	return hp;
}

void Player::UpdateScoreBoard(){
	std::cout <<"HP : "<< hp<< " | Score : " << score  << " | Coins : " << coins << std::endl;
}