#ifndef Box_HEADER
#define Box_HEADER

#include "Object.h"

class Box :public Object {

protected:
	int boxHp;
	const char* normalBoxAsset = "Assets/block_normal.png";
	const char* armoredBoxAsset = "Assets/block_armored.png";
	const char* metalBoxAsset = "Assets/block_metal.png";
	const char* hardBoxAsset = "Assets/block_hard.png";
	const char* veryHardBoxAsset = "Assets/block_veryhard.png";
	const char* extremeBoxAsset = "Assets/block_xtreme.png";
	const char* specialBoxAsset = "Assets/block_special.png";
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
	Box(SDL_Renderer* rend, const char* assetPath, ObjectType ot);
	void DamageBox(SDL_Renderer* rend, int dmg);
	void SetBoxHp(int hp);
	void SetBoxHp(char ch);
	int GetBoxHp();
	void SetBoxColorAndType(char ch);
	void UpdateBoxColorAndTexture(SDL_Renderer* rend);
};



#endif // !Box_HEADER