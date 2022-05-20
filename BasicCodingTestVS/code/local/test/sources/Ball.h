#ifndef Ball_HEADER
#define Ball_HEADER

#include "Object.h"

class Ball :public Object{
protected:

	int ballStrength;
public:
	int playerContact;
	Ball();
	Ball(Renderer::Color c, ObjectType ot);
	Ball(SDL_Renderer* rend, const char* assetPath, ObjectType ot);
	void SetStrength(int x);
	int GetStrength();
	void SpeedUp(int i);
};



#endif // !Ball_HEADER
