#include "gamebase.hpp"
#include "renderer.hpp"
#include "game.hpp"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

int main(  )
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* pWindow = SDL_CreateWindow("Game",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			512, 512,
			0);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	Renderer renderer(pRenderer);

	GameBase* pGame = new Game();


	float mouseX = 256;
	float mouseY = 256;
	bool mousePressed = false;

	bool running = true;
	unsigned int lastTime = SDL_GetTicks();
	while(running) {
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
				break;
			case SDL_MOUSEMOTION:
				mouseX = ( float )event.motion.x;
				mouseY = ( float )event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mousePressed = true;
				break;
			case SDL_MOUSEBUTTONUP:
				mousePressed = false;
				break;
			}
		}

		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(pRenderer);

		unsigned int time = SDL_GetTicks();
		float timeStep = (time - lastTime) / 1000.0f;
		lastTime = time;
		pGame->update(timeStep, mouseX, mouseY, mousePressed);
		pGame->render(renderer);

		SDL_RenderPresent(pRenderer);
	}

	delete pGame;

	SDL_Quit();
	return 0;
}
