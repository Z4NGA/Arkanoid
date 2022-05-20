#include "GameEngine.h"

GameEngine::GameEngine() {
    CreateWindow();
    CreateRenderer(render_flags);
    level = 1;
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

bool GameEngine::HandleCollision(Object* o, Object* collider) {
    //generalized the player to ball collision to work on other objects
    int ballX = o->transform.x, ballY = o->transform.y, colliderX = collider->transform.x, colliderY = collider->transform.y;
    int ballW = o->transform.w, ballH = o->transform.h, colliderW = collider->transform.w, colliderH = collider->transform.h;
    int r1 = ballX + ballW, r2 = colliderX + colliderW, l1 = ballX, l2 = colliderX, t1 = ballY, t2 = colliderY, b1 = ballY + ballH, b2 = colliderY + colliderH;
    //left, right top botom positions for both objects
    int ballCenterX = (ballX + ballW) / 2;
    int colliderCenterX = (colliderX + colliderW) / 2;
    const int collisionTolerance = 3;//this is to be tolerant with collision to colliders

    bool isColliding = true;
    if (r1<l2 || l1>r2 || t1 > b2 || b1 < t2)//easier to find when they don't collide
    {
        //isColliding = false;
        return false;
    }
    if (isColliding) {
        if (t1<(t2 + collisionTolerance) || b1>(b2 - collisionTolerance))//invert velocity in case ball hit by the top or bott of palyer
            o->VelocityY = -o->VelocityY;
        if ((ballCenterX < colliderCenterX && o->VelocityX > 0) || (ballCenterX > colliderCenterX && o->VelocityX < 0)) 
            o->VelocityX = -o->VelocityX; //invert the x velocity based on the hit position
        
    }
    return isColliding;
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
        const int collisionTolerance = 3;//this is to be tolerant with players saving the ball at the last second

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
            player->SetHp(player->GetHp() - 1);
            cout << "Ball touch the ground -1 HP !!!\n";
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

        //vector<Box*>::iterator q = targetableObjects->begin();
        for (auto box : *targetableObjects) {
            if (box->boxState != Box::DESTROYED) {
                //targetableObjects->erase(q);
                if (HandleCollision(o, box)) {
                    //cout << "handling box collision\n";
                    box->DamageBox(rend, ((Ball*)o)->GetStrength());
                    player->UpdateScore();
                    if(box->boxState==Box::DESTROYED){
                        player->UpdateScore(10 * (int)box->boxType+10);
                        player->AddCoins(50*(int)box->boxType+50);
                    }
                }
            }
        }
        HandleCollision(o, player);
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
    targetableObjects = new vector<Box*>();
    for (size_t i = 0; i < mapConfig->size(); i++)
    {
        auto xPosIndex = 0;
        gameMap->push_back(new vector<Object*>());
        for (auto ch : mapConfig->at(i))
        {
            Object* objectTemp;
            Box* boxTemp;
            switch (ch)
            {
            case 'e':
            case ' ':
                objectTemp = new Object(Renderer::BLACK, Object::Empty);
                objectTemp->SetSize(16, 16);
                objectTemp->SetPosition(xPosIndex * objectTemp->fixedSize, i * objectTemp->fixedSize);
                gameMap->at(i)->push_back(objectTemp);
                break;
            case 'b': //normal box
            case 'a': //armored box
            case 'm': //metal box
            case 'h': //hard to break box
            case 'v': //very hard to break box
            case 'x': //extremely hard to break box
                objectTemp = new Box(rend,"Assets/block_normal.png", Object::BOX);
                objectTemp->SetSize(16, 16);
                objectTemp->SetPosition(xPosIndex * objectTemp->fixedSize, i * objectTemp->fixedSize);
                gameMap->at(i)->push_back(objectTemp);
                boxTemp = (Box*)objectTemp;
                boxTemp->SetBoxHp(ch);
                boxTemp->SetBoxColorAndType(ch);
                boxTemp->UpdateBoxColorAndTexture(rend);
                targetableObjects->push_back(boxTemp);
                break;
            default:
                objectTemp = new Object(Renderer::BLACK, Object::Empty);
                objectTemp->SetSize(16, 16);
                objectTemp->SetPosition(xPosIndex * objectTemp->fixedSize, i * objectTemp->fixedSize);
                gameMap->at(i)->push_back(objectTemp);
                break;
            }
            xPosIndex++;
        }
    }
}
Player* GameEngine::AddPlayer(bool withText) {
    if (withText) {
        cout << "asset path not none";
        auto objectTemp = new Player(rend,"Assets/bar_gold_48_16.png", Object::PLAYER);
        objectTemp->SetSize(48, 16, false);
        objectTemp->SetPosition((GameSpaceWidth - objectTemp->transform.w) / 2, 800);//centered x, fixed y for now
        player = (Player*)objectTemp;
    }
    else {
        auto objectTemp = new Player(Renderer::RED, Object::PLAYER);
        objectTemp->SetSize(48, 16, false);
        objectTemp->SetPosition((GameSpaceWidth - objectTemp->transform.w) / 2, 800);//centered x, fixed y for now
        player = (Player*)objectTemp;
    }
    return player;
}

Ball* GameEngine::AddBall(bool withText) {
    if (withText) {
        auto objectTemp = new Ball(rend,"Assets/ball_gold_16_16.png", Object::BALL);
        objectTemp->SetSize(16, 16, false);
        objectTemp->SetPosition((GameSpaceWidth - objectTemp->transform.w) / 2, 750);//centered x, fixed y for now
        objectTemp->isMoving = true;
        ball = (Ball*)objectTemp;
    }
    else {
        auto objectTemp = new Ball(Renderer::GREEN, Object::BALL);
        objectTemp->SetSize(16, 16, false);
        objectTemp->SetPosition((GameSpaceWidth - objectTemp->transform.w) / 2, 750);//centered x, fixed y for now
        objectTemp->isMoving = true;
        ball = (Ball*)objectTemp;
    }
    return ball;
}

void GameEngine::DrawBorder(float x, float y, float w, float h, Renderer::Color c) {
    SDL_SetRenderDrawColor(rend, (Uint8)((c >> 16) & 255), (Uint8)((c >> 8) & 255), (Uint8)(c & 255), (Uint8)255);
    SDL_Rect rect;
    rect.x = (int)x;
    rect.y = (int)y;
    rect.w = (int)w;
    rect.h = (int)h;
    SDL_RenderFillRect(rend, &rect);
}
void GameEngine::DrawBorder(float w, float h, Renderer::Color c) {
    SDL_SetRenderDrawColor(rend, (Uint8)((c >> 16) & 255), (Uint8)((c >> 8) & 255), (Uint8)(c & 255), (Uint8)255);
    SDL_Rect botRect,rightRect;
    rightRect.x = (int)w;
    rightRect.y = 0;
    rightRect.w = 5;
    rightRect.h = (int)h;
    botRect.x = 0;
    botRect.y = (int)h;
    botRect.w = (int)w;
    botRect.h = 5;
    SDL_RenderFillRect(rend, &rightRect);
    SDL_RenderFillRect(rend, &botRect);
}

void GameEngine::ClearAndRender() {
    SDL_RenderClear(rend);
    //change for all objects
    for (size_t i = 0; i < gameMap->size(); i++)
    {
        for (Object* o : *(gameMap->at(i)))
        {
            if (o->type == Object::BOX) {
                if (((Box*)o)->boxState != Box::DESTROYED)
                    o->DrawObject(rend);
            }
            //else    o->DrawObject(rend);
        }
    }

    //simulating a higher layer Zposition
    player->DrawObject(rend);
    //draw player hp
    for (auto o : *(player->playerHpObjects))
    {
        o->DrawObject(rend);
    }
    //draw ball
    ball->DrawObject(rend);
    DrawBorder(GameSpaceWidth, GameSpaceHeight, Renderer::WHITE);
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
    for (auto o : *targetableObjects) {
        if (o->renderType == Object::TEXTURE) {
            SDL_DestroyTexture(o->texture);
        }
    }
    if (player->renderType == Object::TEXTURE) {
        SDL_DestroyTexture(player->texture);
    }
    if (ball->renderType == Object::TEXTURE) {
        SDL_DestroyTexture(ball->texture);
    }
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

void GameEngine::BoxesGoDown() {
    for (auto box : *targetableObjects) {
        box->transform.y += box->fixedSize;
    }
}

void GameEngine::StartLevel(int i, vector<vector<char>>* mapConfig) {
    ResetPlayer();
    ResetBall();
    GenerateMap(mapConfig);
    level = i;
}
void GameEngine::ResetPlayer() {
    player->SetPosition((GameSpaceWidth - player->transform.w) / 2, 800);//centered x, fixed y for now
    player->SetHp(5);
}
void GameEngine::ResetBall() {
    ball->SetPosition((GameSpaceWidth - ball->transform.w) / 2, 750);//centered x, fixed y for now
    ball->isMoving = true;
    ball->SetVelocity(0, 0);
}
bool GameEngine::CheckWinCondition() {
    for (auto box : *targetableObjects) {
        if (box->boxState != Box::DESTROYED) {
            return false;
        }
    }
    return true;
}

bool GameEngine::CheckLoseCondition() {
    return player->GetHp() <= 0;
}
void GameEngine::ShootBullet() {
    auto bullet = new Object(Renderer::WHITE, Object::BULLET);
    bullet->SetSize(3, 3, false);
    bullet->SetPosition(player->transform.w / 2, player->transform.y-3);//centered x, fixed y for now
    bullet->SetVelocity(0, -10);
    player->shootCooldown = true;
}