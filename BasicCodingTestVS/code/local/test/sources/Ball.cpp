#include "Ball.h"


Ball::Ball() :Object(){

}
Ball::Ball(Renderer::Color c, ObjectType ot): Object(c, ot) {
	ballStrength = 1;
}
Ball::Ball(SDL_Renderer* rend, const char* assetPath, ObjectType ot) : Object(rend, assetPath, ot) {
	ballStrength = 1;
}
void Ball::SetStrength(int x) {
	ballStrength = x;
}
int Ball::GetStrength() {
	return ballStrength;
}

void Ball::SpeedUp(int i) {
	VelocityX = VelocityX < 0 ? VelocityX - i : VelocityX + i;
	VelocityY = VelocityY < 0 ? VelocityY - i : VelocityY + i;
}