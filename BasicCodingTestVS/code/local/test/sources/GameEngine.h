#ifndef GameEngine_HEADER
#define GameEngine_HEADER

#include "SDL2/SDL.h"
//#include "SDL_image.h"
#include "Object.h"
#include "Player.h"
#include "GameEvent.h"
#include "Ball.h"
#include "Box.h"
#include <cstdlib>
#include <iostream>
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
	Ball* ball;
	vector<Box*>* targetableObjects;
public:
	//reserving 750*500 for game map rest for player and ui
	static const int ScreenWidth = 900, ScreenHeight = 900;
	static const int GameSpaceWidth = 500, GameSpaceHeight = 850;
	bool isPlaying = true;
	GameEngine();
	~GameEngine();
	void CreateWindow();
	void CreateRenderer(Uint32 flags);
	void ShutDown();
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	GameEvent HandleKeyboard(SDL_Event event);
	void HandleBorderCollision(Object* o);
	bool HandleCollision(Object* o, Object* collider);
	void GenerateMap(vector<vector<char>>* mapConfig);
	void ClearAndRender();
	Player* GetPlayer();
	Player* AddPlayer();
	Ball* AddBall();
	Ball* GetBall();
	void DrawBorder(float x, float y, float w, float h, Renderer::Color c);
	void DrawBorder(float w, float h, Renderer::Color c);
};


#endif // !GameEngine_HEADER