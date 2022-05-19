#include "Box.h"


Box::Box() :Object() {

}
Box::Box(Renderer::Color c, ObjectType ot) : Object(c, ot) {
	boxHp = 1;
	boxState = FULL_HP;
}


void Box::DamageBox(int dmg) {
	if(boxHp!=NULL & boxHp>0) boxHp-= dmg;
	if (boxHp <= 0) boxState = DESTROYED;
	else boxState = DAMAGED;
}
void Box::SetBoxHp(int hp) {
	boxHp = hp;
}
int Box::GetBoxHp() {
	return boxHp;
}
