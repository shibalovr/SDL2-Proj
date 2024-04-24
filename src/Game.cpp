#include "Game.h"


Game* Game::s_Instance = nullptr;
SDL_Renderer* Game::renderer = nullptr;
Character* charac = nullptr;
Game::Game(){}

Game* Game::getInstance() {
    if (!s_Instance) {
        s_Instance = new Game();
    }
    return s_Instance;
}


void Game::init(const char* title, int xpos, int ypos, bool fullscreen) {
    menu = true;
    quit = false;
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    quit = false;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        printf("Subsystems Initialised!\n");

        window = SDL_CreateWindow(title, ypos, xpos, WIDTH, HEIGHT, flags);
        if (window) {
            printf("Window created!\n");
        }

        Game::renderer = SDL_CreateRenderer(window, -1, 0);
        if (Game::renderer) {
            printf("Renderer created\n");
        }
    } else {
        quit = true;
    }
    TextureManager::GetInstance()->Load("idle", "assets/sprites/idle.png");
    TextureManager::GetInstance()->Load("walk", "assets/sprites/walk.png");
    TextureManager::GetInstance()->Load("crouch", "assets/sprites/crouch.png");
    TextureManager::GetInstance()->Load("jump_up", "assets/sprites/jump_up.png");
    TextureManager::GetInstance()->Load("jump_down", "assets/sprites/jump_down.png");
    charac = new Character(new Properties("idle", 500, 3800, 32, 28, 2));
    Map::GetInstance()->LoadTileSets("assets/map/ts.png");
    Camera::GetInstance()->setTarget(charac->GetOrigin());
    ColHandler::GetInstance()->LoadCollider("assets/map/bg_wall.csv");
}


void Game::handleEvents() {
    Input::getInstance()->Listen();
}

void Game::update() {  
    float dt = Timer::getInstance()->getDeltaTime();
    charac->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Game::render() {
    SDL_RenderClear(Game::renderer);
    Map::GetInstance()->LoadMap(0, "assets/map/bg_bg.csv");
    Map::GetInstance()->LoadMap(1, "assets/map/bg_wall.csv");
    charac->Draw();
    SDL_RenderPresent(Game::renderer);
}

void Game::Quit(){ 
    quit = true;
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    TextureManager::GetInstance()->clean();
    delete charac;
    Map::GetInstance()->Clean();
    printf("Game cleaned!");
    SDL_Quit();
}