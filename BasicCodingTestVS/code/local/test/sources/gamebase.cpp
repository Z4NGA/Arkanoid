#include "gamebase.hpp"
#include "renderer.hpp"
#include "game.hpp"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "MapEngine.h"
#include "GameEngine.h"
int main(  )
{

	//creating a mapengine for reading level maps
	MapEngine* map = new MapEngine();
	//creating game engine for rendering game elements and handling physics related stuff
	GameEngine* engine = new GameEngine();

	//loading the map of the first level
	map->LoadMap(1);
	//map->PrintMap();

	//creating a player
	Player* p = engine->AddPlayer(true);
	//adding a ball
	Ball* ball = engine->AddBall(true);
	//starting the first level
	engine->StartLevel(1,map->GetMap());

	//initializing mouse positions
	float mouseX = 256;
	float mouseY = 256;
	bool mousePressed = false;
	//initializing testing variable
	bool skipLevelHack = false;
	//priting a simple tutorial
	cout << "Click on the mouse button to start !!!\n Destroy All blocks to go to the next level\n move using the arrows\n once the ball stops click on the mouse to continue\n use escape to leave\n You start with 5 Hp and lose 1 if the ball touch the floor\nearn score and points by destroying the blocks\n";
	bool running = engine->isPlaying;
	unsigned int lastTime = SDL_GetTicks();
	//game loop
	while(running & engine->isPlaying) {
		//handling user input
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
				else if (event.key.keysym.sym == SDLK_SPACE) {
					cout << "shooting now\n";
					if (!engine->GetPlayer()->shootCooldown) {
						engine->ShootBullet();
						//engine->GetPlayer()->shootCooldown = true;
					}
				}
				else if (event.key.keysym.sym == SDLK_l) {
					skipLevelHack = true;
				}
				else engine->GetPlayer()->Move(engine->HandleKeyboard(event));
				break;
			case SDL_MOUSEMOTION:
				mouseX = ( float )event.motion.x;
				mouseY = ( float )event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mousePressed = true;
				if(engine->GetBall()->VelocityX==0 && engine->GetBall()->VelocityY == 0) engine->GetBall()->SetVelocity(5, -5);
				break;
			case SDL_MOUSEBUTTONUP:
				mousePressed = false;
				break;
			}
		}
		//handling object physics
		engine->MoveAllObjects();
		engine->HandleAllCollisions();

		engine->ClearAndRender();

		unsigned int time = SDL_GetTicks();
		float timeStep = (time - lastTime) / 1000.0f;
		
		if(timeStep>=10){
		lastTime = time;
		engine->BoxesGoDown();
		ball->SpeedUp(1);
		}
		//checking win conditions
		if (engine->CheckWinCondition() || skipLevelHack) {
			skipLevelHack = false;
			engine->level++;
			if (engine->level > 7) { 
				cout << "##########################\nYOU WIN THE GAME !!!!!!!\n###############################";
				running = false;
			}
			map->LoadMap(engine->level);
			engine->StartLevel(engine->level, map->GetMap());
		}
		//checking losing condition
		if (engine->CheckLoseCondition()) {
			cout << "##########################\nYOU LOSE THE GAME !!!!!!!\n###############################";
			running = false;
		}
	}

	//clean & shutdown
	engine->ShutDown();
	return 0;
}
