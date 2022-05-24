#ifndef Ball_HEADER
#define Ball_HEADER

#include "Object.h"

/*
* @class: the ball class
*/
class Ball :public Object{
protected:

	int ballStrength;
public:
	int playerContact;
	Ball();
	Ball(Renderer::Color c, ObjectType ot);
	Ball(SDL_Renderer* rend, const char* assetPath, ObjectType ot);
	/*
	* @brief sets the ball's hit strength
	*/
	void SetStrength(int x);
	/*
	* @return: returns the ball's hit strength
	*/
	int GetStrength();
	/*
	* @brief: speeds up the balls velocity with i
	*/
	void SpeedUp(int i);
};



#endif // !Ball_HEADER
