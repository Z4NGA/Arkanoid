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
	enum BoxType {
		NORMAL =1,
		ARMORED=2,
		METAL=3,
		HARD=4,
		VERY_HARD=5,
		XTREME=7
	};
	BoxState boxState;
	BoxType boxType;
	Box();
	Box(Renderer::Color c, ObjectType ot);
	void DamageBox(int dmg);
	void SetBoxHp(int hp);
	void SetBoxHp(char ch);
	int GetBoxHp();
	void SetBoxColor(char ch);
	void UpdateBoxColorAndType();
};



#endif // !Box_HEADER
