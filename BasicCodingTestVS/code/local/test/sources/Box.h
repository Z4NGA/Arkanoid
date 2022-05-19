#ifndef Box_HEADER
#define Box_HEADER

#include "Object.h"

class Box :public Object {

protected:
	int boxHp;
	
public:
	enum BoxState
	{
		FULL_HP,
		DAMAGED,
		DESTROYED,
		REPARING,
	};
	BoxState boxState;
	Box();
	Box(Renderer::Color c, ObjectType ot);
	void DamageBox(int dmg);
	void SetBoxHp(int hp);
	int GetBoxHp();

};



#endif // !Box_HEADER
