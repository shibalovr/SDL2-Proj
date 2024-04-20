#include "Game.h"


Game* Game::s_Instance = nullptr;
SDL_Renderer* Game::renderer = nullptr;
Character* charac = nullptr;
Enemy* bat = nullptr;
Game::Game(){}

Game* Game::getInstance() {
    if (!s_Instance) {
        s_Instance = new Game();
    }
    return s_Instance;
}


void Game::init(const char* title, int xpos, int ypos, bool fullscreen) {
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
    TextureManager::GetInstance()->Load("roll", "assets/sprites/roll.png");
    TextureManager::GetInstance()->Load("attack", "assets/sprites/attack.png");
    TextureManager::GetInstance()->Load("bat", "assets/sprites/enemy/bat_fly.png");
    charac = new Character(new Properties("idle", 600, 800, 64, 64, 4));
    bat = new Enemy(new Properties("bat", 600, 800, 64, 64, 5));
    bat->SetMovingArea(720, 920, 500, 500);
    Map::GetInstance()->LoadTileSets("assets/map/tileset.png");
    Camera::GetInstance()->setTarget(charac->GetOrigin());
    ColHandler::GetInstance()->LoadCollider("assets/map/map1_Collider.csv");
}


void Game::handleEvents() {
    Input::getInstance()->Listen();
}

void Game::update() {  
    float dt = Timer::getInstance()->getDeltaTime();
    printf("%f\n", dt);
    charac->Update(dt);
    bat->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Game::render() {
    SDL_RenderClear(Game::renderer);
    Map::GetInstance()->LoadMap(0, "assets/map/map1_bg.csv");
    // Map::GetInstance()->LoadMap(1, "assets/map/object.csv");
    charac->Draw();
    bat->Draw();
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
    delete bat;
    Map::GetInstance()->Clean();
    printf("Game cleaned!");
    SDL_Quit();
}