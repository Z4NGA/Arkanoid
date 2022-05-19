#include "Ball.h"


Ball::Ball() :Object(){

}
Ball::Ball(Renderer::Color c, ObjectType ot): Object(c, ot) {
	ballStrength = 1;
}
void Ball::SetStrength(int x) {
	ballStrength = x;
}
int Ball::GetStrength() {
	return ballStrength;
}