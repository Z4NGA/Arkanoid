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
	GameEngine* engine = new GameEngine();


	map->LoadMap(1);
	
	map->PrintMap();

	Player* p = engine->AddPlayer(true);
	Ball* ball = engine->AddBall(true);

	engine->StartLevel(1,map->GetMap());

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
	cout << "Click on the mouse button to start !!!\n Destroy All blocks to go to the next level\n move using the arrows\n once the ball stops click on the mouse to continue\n use escape to leave\n You start with 5 Hp and lose 1 if the ball touch the floor\nearn score and points by destroying the blocks\n";
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
				else if (event.key.keysym.sym == SDLK_SPACE) {
					cout << "shooting now\n";
					if (!engine->GetPlayer()->shootCooldown) {
						engine->ShootBullet();
						engine->GetPlayer()->shootCooldown = true;
					}
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
		
		if(timeStep>=10){
		lastTime = time;
		engine->BoxesGoDown();
		ball->SpeedUp(1);
		}
		if (engine->CheckWinCondition()) {
			engine->level++;
			if (engine->level > 7) { 
				cout << "##########################\nYOU WIN THE GAME !!!!!!!\n###############################";
				running = false;
			}
			map->LoadMap(engine->level);
			engine->StartLevel(engine->level, map->GetMap());
		}
		if (engine->CheckLoseCondition()) {
			cout << "##########################\nYOU LOSE THE GAME !!!!!!!\n###############################";
			running = false;
		}
		//pGame->update(timeStep, mouseX, mouseY, mousePressed);
		//pGame->render(renderer);

		//SDL_RenderPresent(pRenderer);
	}

	//clean & shutdown
	engine->ShutDown();
	return 0;
}
