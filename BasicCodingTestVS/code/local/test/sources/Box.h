#ifndef Box_HEADER
#define Box_HEADER

#include "Object.h"

/*
* @class: the class that handles the box's working and states
*/
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
	/*
	* @brief damages the box with the dmg variable, the object visuals are also updated
	*/
	void DamageBox(SDL_Renderer* rend, int dmg);
	/*
	* @brief sets the box's hp
	*/
	void SetBoxHp(int hp);
	/*
	* @brief sets the box's hp depending on the box type 'ch' in the map configuration 
	*/
	void SetBoxHp(char ch);
	/*
	* @return: returns the box's hp
	*/
	int GetBoxHp();
	/*
	* @brief sets the box's color and type depending on the map configuration 'ch'
	*/
	void SetBoxColorAndType(char ch);
	/*
	* @brief updates the box's color and texture depending on the box's hp
	*/
	void UpdateBoxColorAndTexture(SDL_Renderer* rend);
};



#endif // !Box_HEADER