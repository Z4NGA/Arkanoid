#include "GameEngine.h"

GameEngine::GameEngine() {
    CreateWindow();
    CreateRenderer(render_flags);
}
GameEngine::~GameEngine() {
}
SDL_Window* GameEngine::GetWindow() {
    return this->win;
}
SDL_Renderer* GameEngine::GetRenderer()
{
    return rend;
}
GameEvent GameEngine::HandleKeyboard(SDL_Event event) {
    //just to understand the keyboard system of sdl
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_X:
        return GameEvent::ATTACK;
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
    case SDL_SCANCODE_SPACE:
        return GameEvent::MOVE_UP;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
        return GameEvent::MOVE_LEFT;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
        return GameEvent::MOVE_DOWN;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
        return GameEvent::MOVE_RIGHT;
    default:
        return GameEvent::UNDEFINED;
    }
}

void GameEngine::HandleBorderCollision(SDL_Rect& transform)
{

    // right boundary
    if (transform.x + transform.w > 1000)
        transform.x = 1000 - transform.w;

    // left boundary
    if (transform.x < 0)
        transform.x = 0;

    // bottom boundary
    if (transform.y + transform.h > 1000)
        transform.y = 1000 - transform.h;

    // upper boundary
    if (transform.y < 0)
        transform.y = 0;
}

void GameEngine::GenerateMap(vector<vector<char>>* mapConfig)
{
    gameMap = new vector<vector<Object*>*>();
    for (size_t i = 0; i < mapConfig->size(); i++)
    {
        auto xPosIndex = 0;
        gameMap->push_back(new vector<Object*>());
        for (auto ch : mapConfig->at(i))
        {
            Object* objectTemp;
            switch (ch)
            {
            case 'e':
                objectTemp = new Object(Renderer::BLACK, Object::Empty);
                objectTemp->SetSize(25, 25);
                objectTemp->SetPosition(xPosIndex * objectTemp->fixedSize, i * objectTemp->fixedSize);
                gameMap->at(i)->push_back(objectTemp);
                break;
            case 'b':
                objectTemp = new Object(Renderer::BLUE, Object::BOX);
                objectTemp->SetSize(25, 25);
                objectTemp->SetPosition(xPosIndex * objectTemp->fixedSize, i * objectTemp->fixedSize);
                gameMap->at(i)->push_back(objectTemp);
                break;
            case 'p':
                objectTemp = new Player(Renderer::RED, Object::PLAYER);
                objectTemp->SetSize(25, 25);
                objectTemp->SetPosition(xPosIndex * objectTemp->fixedSize, i * objectTemp->fixedSize);
                player = (Player*)objectTemp;
                gameMap->at(i)->push_back(objectTemp);
                break;
            default:
                break;
            }
            xPosIndex++;
        }
    }
}

void GameEngine::ClearAndRender() {
    SDL_RenderClear(rend);
    //change for all objects
    for (size_t i = 0; i < gameMap->size(); i++)
    {
        for (Object* o : *(gameMap->at(i)))
        {
            if (o->type != Object::PLAYER)
                o->DrawObject(rend);
        }
    }

    //simulating a higher layer Zposition
    player->DrawObject(rend);

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(rend);
}

void GameEngine::CreateWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        //printf("error initializing SDL: %s\n", SDL_GetError());
    }
    this->win = SDL_CreateWindow("SDL_GAME",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        GameEngine::ScreenWidth, GameEngine::ScreenHeight, 0);
    //SDL_Delay(3000);
}

void GameEngine::CreateRenderer(Uint32 flags) {

    // creates a renderer to render our images
    this->rend = SDL_CreateRenderer(this->win, -1, flags);
    SDL_SetRenderDrawColor(this->rend, 1, 1, 1, 1);
}

void GameEngine::ShutDown()
{
    
    // destroy renderer
    SDL_DestroyRenderer(rend);

    // destroy window
    SDL_DestroyWindow(win);

    // close SDL
    SDL_Quit();

}

Player* GameEngine::GetPlayer() {
    return player;
}
