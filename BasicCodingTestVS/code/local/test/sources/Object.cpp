#include "Object.h"
Object::Object() {

}
Object::Object(Renderer::Color c, Object::ObjectType ot) {
	color = c;
	type = ot;
	VelocityX = 0;
	VelocityY = 0;
	isMoving = false;
}
void Object::DrawObject(SDL_Renderer* rend) {
	SDL_SetRenderDrawColor(rend, (Uint8)((color >> 16) & 255), (Uint8)((color >> 8) & 255), (Uint8)(color & 255), (Uint8)255);
	SDL_RenderFillRect(rend, &transform);
}
Object::~Object() {

}
void Object::SetSize(int w, int h, bool fixedSize) {
	//u_sing fixed size for now
	if (fixedSize) {
	transform.w = fixedSize;
	transform.h = fixedSize;
	}
	transform.w = w;
	transform.h = h;
}
void Object::SetPosition(int x, int y) {
	transform.x = x;
	transform.y = y;
}
void Object::Move(int x, int y) {
	transform.x = isMoving ? transform.x + x + VelocityX : transform.x + x;
	transform.y = isMoving ? transform.y + y + VelocityY : transform.y + y;
}

void Object::Move(GameEvent e)
{
	switch (e) {
	case GameEvent::MOVE_LEFT:
		Move(-2*fixedSize, 0);
		break;
	case GameEvent::MOVE_RIGHT:
		Move(2*fixedSize, 0);
		break;
	case GameEvent::MOVE_UP:
		Move(0, -fixedSize);
		break;
	case GameEvent::MOVE_DOWN:
		Move(0, fixedSize);
		break;
	case GameEvent::ATTACK:
		std::cout << "Pressed the Attacking BTN !!" << std::endl;
		break;
	case GameEvent::UNDEFINED:
		break;
	}
}
void Object::SetVelocity(int x, int y) {
	VelocityX = x;
	VelocityY = y;
}