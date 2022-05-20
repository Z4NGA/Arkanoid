#include "Object.h"
Object::Object() {

}
Object::Object(Renderer::Color c, Object::ObjectType ot) {
	color = c;
	type = ot;
	VelocityX = 0;
	VelocityY = 0;
	isMoving = false;
	renderType = COLOR;
}

Object::Object(SDL_Renderer* rend, const char* assetPath, ObjectType ot) {
	SDL_Surface* surface;
	// please provide a path for your image
	surface = IMG_Load(assetPath);
	// loads image to our graphics hardware memory.
	texture = SDL_CreateTextureFromSurface(rend, surface);
	// clears main-memory
	SDL_FreeSurface(surface);
	// connects our texture with transform to control position
	SDL_QueryTexture(texture, NULL, NULL, &transform.w, &transform.h);
	type = ot;
	VelocityX = 0;
	VelocityY = 0;
	isMoving = false;
	renderType = TEXTURE;
}

void Object::DrawObject(SDL_Renderer* rend) {
	if (renderType == COLOR) {
		SDL_SetRenderDrawColor(rend, (Uint8)((color >> 16) & 255), (Uint8)((color >> 8) & 255), (Uint8)(color & 255), (Uint8)255);
		SDL_RenderFillRect(rend, &transform);
	}
	else {
		SDL_RenderCopy(rend, texture, NULL, &transform);
	}
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
		break;
	case GameEvent::MOVE_DOWN:
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