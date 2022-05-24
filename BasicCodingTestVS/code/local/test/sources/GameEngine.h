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

/*
*@class: the engine of the game which handles all physics related stuff, SDL configurations,rendering objects
*        and other game objects related stuff
*/
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
	Object* bullet;
public:
	int level;
	//reserving 864*512 for game map rest for player and ui
	static const int ScreenWidth = 900, ScreenHeight = 900;
	static const int GameSpaceWidth = 512, GameSpaceHeight = 864;
	bool isPlaying = true;
	GameEngine();
	~GameEngine();
	/*
	* @brief: creates game window with the defined configuration : height , width
	* @return:
	*/
	void CreateWindow();
	/*
	* @brief: creates a sdl renderer using the defined flags
	*/
	void CreateRenderer(Uint32 flags);
	/*
	* @brief: cleans the textures, destroys the renderer and shuts down the game
	*/
	void ShutDown();
	/*
	* @return: returns the game window
	*/
	SDL_Window* GetWindow();
	/*
	* @return: returns the sdl renderer
	*/
	SDL_Renderer* GetRenderer();
	/*
	* @brief: handles the user keyboard input
	* @return: an enum value of GameEvent depending on the user input
	*/
	GameEvent HandleKeyboard(SDL_Event event);
	/*
	* @brief: handles all general collisions for an object
	*/
	void HandleBorderCollision(Object* o);
	/*
	* @brief: handles a collision between 2 objects
	* @return: true if objects collide, false otherwise
	*/
	bool HandleCollision(Object* o, Object* collider);
	/*
	* @brief: uses the map configuration to generate a map of game objects
	*/
	void GenerateMap(vector<vector<char>>* mapConfig);
	/*
	* @brief: clears the window and draw game objects
	*/
	void ClearAndRender();
	/*
	* @return: returns the player pointer
	*/
	Player* GetPlayer();
	/*
	* @brief: creates a player, depending on the withText variable , the player is created with texture or colors
	* @return: pointer of the created player
	*/
	Player* AddPlayer(bool withText=false);
	/*
	* @brief: creates a ball, depending on the withText variable , the ball is created with texture or colors
	* @return: pointer of the created ball
	*/
	Ball* AddBall(bool withText = false);
	/*
	* @return: returns a pointer of the ball
	*/
	Ball* GetBall();
	/*
	* @brief: draws the borders that seperates the game space from the ui elements
	*/
	void DrawBorder(float x, float y, float w, float h, Renderer::Color c);
	/*
	* @brief: another variant for creating borders
	*/
	void DrawBorder(float w, float h, Renderer::Color c);
	/*
	* @brief: handles moving the box objects 1 fixedspace down
	*/
	void BoxesGoDown();
	/*
	* @brief: starts the level i, reset other game objects and generates a new map
	*/
	void StartLevel(int i, vector<vector<char>>* mapConfig);
	/*
	* @brief: resets the player position and some of its stats
	*/
	void ResetPlayer();
	/*
	* @brief: resets the ball position, speed and some other stats
	*/
	void ResetBall();
	/*
	* @brief: checks if the player reached the win condition of destroying all boxes
	* @return: true if player won, false otherwise
	*/
	bool CheckWinCondition();
	/*
	* @brief: checks if the player triggered the lose conditions
	* @return: true if player lost, false otherwise
	*/
	bool CheckLoseCondition();
	/*
	* @brief: shoots a bullet from the player pad
	*/
	void ShootBullet();
};


#endif // !GameEngine_HEADER