#ifndef Ball_HEADER
#define Ball_HEADER

#include "Object.h"

class Ball :public Object{
protected:

	int ballStrength;
public:
	Ball();
	Ball(Renderer::Color c, ObjectType ot);
	void SetStrength(int x);
	int GetStrength();

};



#endif // !Ball_HEADER
