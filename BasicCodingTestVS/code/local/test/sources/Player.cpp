#include "Player.h"

Player::Player() :Object() {

}
Player::Player(Renderer::Color c, ObjectType ot) :
	Object(c, ot)
{
	hp = 5;
	score = 0;
	coins = 0;
}

void Player::UpdateScore(int i) {
	score += i;
	std::cout << "Score : " << score << std::endl;
}
void Player::AddCoins(int i) {
	coins += i;
	std::cout << "Coins : " << coins << std::endl;
}
void Player::SetHp(int h) {
	hp = h;
}
int Player::GetHp() {
	return hp;
}