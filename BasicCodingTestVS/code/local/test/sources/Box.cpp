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

void Box::DamageBox(SDL_Renderer* rend, int dmg) {
	if (boxState == DESTROYED)return;
	boxHp-= dmg;
	if (boxHp <= 0) {
		boxState = DESTROYED;
		return;
	}
	UpdateBoxColorAndTexture(rend);
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
void Box::UpdateBoxColorAndTexture(SDL_Renderer* rend) {
	switch (boxHp) {
	case 1:
		if (renderType == COLOR) color = Renderer::YELLOW;
		else ChangeTexture(rend, normalBoxAsset);
		//boxType = NORMAL;
		break;
	case 2:
		if (renderType == COLOR)color = Renderer::DARK_YELLOW;
		else ChangeTexture(rend, armoredBoxAsset);
		//boxType = ARMORED;
		break;
	case 3:
		if (renderType == COLOR)color = Renderer::BLUE;
		else ChangeTexture(rend, metalBoxAsset);
		//boxType = METAL;
		break;
	case 4:
		if (renderType == COLOR)color = Renderer::DARK_BLUE;
		else ChangeTexture(rend, hardBoxAsset);
		//boxType = HARD;
		break;
	case 5:
		if (renderType == COLOR)color = Renderer::MAGENTA;
		else ChangeTexture(rend, veryHardBoxAsset);
		//boxType = VERY_HARD;
		break;
	case 7:
		if (renderType == COLOR)color = Renderer::DARK_MAGENTA;
		else ChangeTexture(rend, extremeBoxAsset);
		//boxType = XTREME;
		break;
	}
}