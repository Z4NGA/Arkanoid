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

void GameEngine::HandleBorderCollision(Object* o)
{
    if(o->type == Object::BALL){
        //simple positions calculations
        int ballX = o->transform.x, ballY = o->transform.y, playerX = player->transform.x, playerY = player->transform.y;
        int ballW = o->transform.w, ballH = o->transform.h, playerW = player->transform.w, playerH = player->transform.h;
        int r1 = ballX + ballW, r2 = playerX + playerW, l1 = ballX, l2 = playerX, t1 = ballY, t2 = playerY, b1 = ballY + ballH, b2 = playerY + playerH;
        //left, right top botom positions for both objects
        int ballCenterX = (ballX + ballW) / 2;
        int playerCenterX = (playerX + playerW) / 2;
        const int collisionTolerance = 5;//this is to be tolerant with players saving the ball at the last second

        // Map Collision
        if (o->transform.x + o->transform.w > GameSpaceWidth) {
            o->transform.x = GameSpaceWidth - o->transform.w;
            o->VelocityX = -o->VelocityX;
            return;
        }
        // left boundary
        if (o->transform.x < 0) {
            o->transform.x = 0;
            o->VelocityX = -o->VelocityX;
            return;
        }
        // bottom boundary
        if (o->transform.y + o->transform.h > GameSpaceHeight) {
            o->transform.y = GameSpaceHeight - o->transform.h;
            o->VelocityY = -o->VelocityY;
            //isPlaying = false;
            return;
        }
        // upper boundary
        if (o->transform.y < 0) {
            o->transform.y = 0;
            o->VelocityY = -o->VelocityY;
            return;
        }
        // ball-to-player collision detection
        bool isColliding = true;
        if (r1<l2 || l1>r2 || t1 > b2 || b1 < t2)//easier to find when they don't collide
            isColliding = false;
        if (isColliding) {
            if (t1<(t2 + collisionTolerance) || b1>(b2 - collisionTolerance))//invert velocity in case ball hit by the top or bott of palyer
                o->VelocityY = -o->VelocityY;
            if ((ballCenterX < playerCenterX && o->VelocityX > 0) || (ballCenterX > playerCenterX && o->VelocityX < 0)) {
                o->VelocityX = -o->VelocityX; //invert the x velocity based on the hit position
            }
        }
        return;
    }
    switch (o->type) {
    case Object::PLAYER:
        if (o->transform.x + o->transform.w > GameSpaceWidth)
            o->transform.x = GameSpaceWidth - o->transform.w;
        // left boundary
        if (o->transform.x < 0)
            o->transform.x = 0;
        break;
    case Object::BOOST:
    case Object::BOMB:
        // bottom boundary
        if (o->transform.y + o->transform.h > GameSpaceHeight)
            o->transform.y = GameSpaceHeight - o->transform.h;
        break;
    }
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
            /*case 'p':
                objectTemp = new Player(Renderer::RED, Object::PLAYER);
                objectTemp->SetSize(25, 25);
                objectTemp->SetPosition(xPosIndex * objectTemp->fixedSize, i * objectTemp->fixedSize);
                player = (Player*)objectTemp;
                gameMap->at(i)->push_back(objectTemp);
                break;
                */
            default:
                objectTemp = new Object(Renderer::BLACK, Object::Empty);
                objectTemp->SetSize(25, 25);
                objectTemp->SetPosition(xPosIndex * objectTemp->fixedSize, i * objectTemp->fixedSize);
                gameMap->at(i)->push_back(objectTemp);
                break;
            }
            xPosIndex++;
        }
    }
}
Player* GameEngine::AddPlayer() {
    auto objectTemp = new Player(Renderer::RED, Object::PLAYER);
    objectTemp->SetSize(125, 25,false);
    objectTemp->SetPosition((GameSpaceWidth-objectTemp->transform.w)  /2, 800);//centered x, fixed y for now
    player = (Player*)objectTemp;
    return player;
}

Ball* GameEngine::AddBall() {
    auto objectTemp = new Ball(Renderer::GREEN, Object::BALL);
    objectTemp->SetSize(15, 15, false);
    objectTemp->SetPosition((GameSpaceWidth - objectTemp->transform.w) / 2, 750);//centered x, fixed y for now
    objectTemp->isMoving = true;
    ball = (Ball*) objectTemp;
    return ball;
}

void GameEngine::ClearAndRender() {
    SDL_RenderClear(rend);
    //change for all objects
    for (size_t i = 0; i < gameMap->size(); i++)
    {
        for (Object* o : *(gameMap->at(i)))
        {
                o->DrawObject(rend);
        }
    }

    //simulating a higher layer Zposition
    player->DrawObject(rend);
    ball->DrawObject(rend);
    //reset draw color to black
    SDL_SetRenderDrawColor(this->rend, 1, 1, 1, 1);
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


Ball* GameEngine::GetBall() {
    return ball;
}