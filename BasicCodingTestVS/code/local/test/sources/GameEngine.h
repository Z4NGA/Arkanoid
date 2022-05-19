#ifndef GameEngine_HEADER
#define GameEngine_HEADER

#include "SDL2/SDL.h"
//#include "SDL_image.h"
#include "Object.h"
#include "Player.h"
#include "GameEvent.h"
#include <cstdlib>
#include <vector>

using namespace std;

class GameEngine
{
protected:
	SDL_Window* win;
	SDL_Renderer* rend;
	Uint32 render_flags = SDL_RENDERER_PRESENTVSYNC;
	vector<vector<Object*>*>* gameMap;
	Player* player;
public:
	static const int ScreenWidth = 1000, ScreenHeight = 1000;

	GameEngine();
	~GameEngine();
	void CreateWindow();
	void CreateRenderer(Uint32 flags);
	void ShutDown();
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	GameEvent HandleKeyboard(SDL_Event event);
	void HandleBorderCollision(SDL_Rect& transform);
	void GenerateMap(vector<vector<char>>* mapConfig);
	void ClearAndRender();
	Player* GetPlayer();
};


#endif // !GameEngine_HEADER