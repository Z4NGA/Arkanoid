#include "Box.h"


Box::Box() :Object() {

}
Box::Box(Renderer::Color c, ObjectType ot) : Object(c, ot) {
	boxHp = 1;
	boxState = FULL_HP;
}
Box::Box(SDL_Renderer* rend, const char* assetPath, ObjectType ot) : Object(rend, assetPath, ot) {
	boxHp = 1;
	boxState = FULL_HP;
}

void Box::DamageBox(int dmg) {
	if (boxState == DESTROYED)return;
	boxHp-= dmg;
	if (boxHp <= 0) {
		boxState = DESTROYED;
		return;
	}
	UpdateBoxColor();
	boxState = DAMAGED;

}
void Box::SetBoxHp(int hp) {
	boxHp = hp;
}
void Box::SetBoxHp(char ch) {
	boxHp = (ch == 'x') ? 7 : (ch == 'v') ? 5 : (ch == 'h') ? 4 : (ch == 'm') ? 3 : (ch == 'a') ? 2 : 1;
}
int Box::GetBoxHp() {
	return boxHp;
}
void Box::SetBoxColorAndType(char ch) {
	color = (ch == 'x') ? Renderer::DARK_MAGENTA
		: (ch == 'v') ? Renderer::MAGENTA
		: (ch == 'h') ? Renderer::DARK_BLUE
		: (ch == 'm') ? Renderer::BLUE
		: (ch == 'a') ? Renderer::DARK_YELLOW
		: Renderer::YELLOW;
	boxType = (ch == 'x') ? XTREME
		: (ch == 'v') ? VERY_HARD
		: (ch == 'h') ? HARD	
		: (ch == 'm') ? METAL
		: (ch == 'a') ? ARMORED
		: NORMAL;
}
void Box::UpdateBoxColor() {
	switch (boxHp) {
	case 1:
		color = Renderer::YELLOW;
		//boxType = NORMAL;
		break;
	case 2:
		color = Renderer::DARK_YELLOW;
		//boxType = ARMORED;
		break;
	case 3:
		color = Renderer::BLUE;
		//boxType = METAL;
		break;
	case 4:
		color = Renderer::DARK_BLUE;
		//boxType = HARD;
		break;
	case 5:
		color = Renderer::MAGENTA;
		//boxType = VERY_HARD;
		break;
	case 7:
		color = Renderer::DARK_MAGENTA;
		//boxType = XTREME;
		break;
	}
}