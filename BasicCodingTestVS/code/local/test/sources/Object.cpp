#include "Object.h"
Object::Object() {

}
Object::Object(Renderer::Color c, Object::ObjectType ot) {
	color = c;
	type = ot;
}
void Object::DrawObject(SDL_Renderer* rend) {
	SDL_SetRenderDrawColor(rend, (Uint8)((color >> 16) & 255), (Uint8)((color >> 8) & 255), (Uint8)(color & 255), (Uint8)255);
	SDL_RenderFillRect(rend, &transform);
}
Object::~Object() {

}
void Object::SetSize(int w, int h) {
	//u_sing fixed size for now
	transform.w = fixedSize;
	transform.h = fixedSize;
}
void Object::SetPosition(int x, int y) {
	transform.x = x;
	transform.y = y;
}
void Object::Move(int x, int y) {
	transform.x += x;
	transform.y += y;
}

void Object::Move(GameEvent e)
{
	switch (e) {
	case GameEvent::MOVE_LEFT:
		Move(-fixedSize, 0);
		break;
	case GameEvent::MOVE_RIGHT:
		Move(fixedSize, 0);
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
