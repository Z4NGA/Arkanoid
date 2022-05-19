/*

eeeeeeeeeeeeeeeebbbbbeeeeeeeeeee
ebbbbbbbbbebbbbbbbbbbbbbebbbbbbb
eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
eeeeeeeeeeeebbbbbbeeeeeeeeeeeeee

read box position map from files
load and convert map to objects
player - ball objects
player controlled with mouse invert x or y based on contact position with the ball
box objects to destroy
score tracking

gameengine to clean the creating of window and keyboard handling 

*/
#include "gamebase.hpp"
#include "renderer.hpp"
#include "game.hpp"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "MapEngine.h"
#include "GameEngine.h"
int main(  )
{

	MapEngine* map = new MapEngine();
	map->LoadMap();
	cout << "printing the map !!\n";
	map->PrintMap();

	GameEngine* engine = new GameEngine();

	engine->GenerateMap(map->GetMap());

	Player* p = engine->AddPlayer();
	Ball* ball = engine->AddBall();
	/*SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* pWindow = SDL_CreateWindow("Game",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			512, 512,
			0);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	Renderer renderer(pRenderer);

	GameBase* pGame = new Game();

	*/
	float mouseX = 256;
	float mouseY = 256;
	bool mousePressed = false;

	bool running = engine->isPlaying;
	unsigned int lastTime = SDL_GetTicks();
	while(running & engine->isPlaying) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
				else engine->GetPlayer()->Move(engine->HandleKeyboard(event));
				break;
			case SDL_MOUSEMOTION:
				mouseX = ( float )event.motion.x;
				mouseY = ( float )event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mousePressed = true;
				engine->GetBall()->SetVelocity(5, -5);
				break;
			case SDL_MOUSEBUTTONUP:
				mousePressed = false;
				break;
			}
		}
		engine->GetBall()->Move(0, 0);
		engine->HandleBorderCollision(engine->GetPlayer());
		engine->HandleBorderCollision(engine->GetBall());

		engine->ClearAndRender();

		//SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
		//SDL_RenderClear(pRenderer);

		unsigned int time = SDL_GetTicks();
		float timeStep = (time - lastTime) / 1000.0f;
		lastTime = time;
		//pGame->update(timeStep, mouseX, mouseY, mousePressed);
		//pGame->render(renderer);

		//SDL_RenderPresent(pRenderer);
	}

	//clean & shutdown
	engine->ShutDown();
	return 0;
}
