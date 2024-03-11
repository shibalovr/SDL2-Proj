#include "Game.h"

Game* Game::s_Instance = nullptr;
SDL_Renderer* Game::renderer = nullptr;
Ninja* test = nullptr;


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
    
    TextureManager::GetInstance()->Load("bg", "assets/backgrounds/bg.png");
    TextureManager::GetInstance()->Load("character_idle", "assets/sprites/Character_idle.png");
    TextureManager::GetInstance()->Load("character_walk", "assets/sprites/Character_walk.png");
    test = new Ninja(new Properties("character_idle", 100, 200, 64, 64));
}


void Game::handleEvents() {
    Input::getInstance()->Listen();
}

void Game::update() {  
    
    test->Update();
}

void Game::render() {
    SDL_RenderClear(Game::renderer);
    
    TextureManager::GetInstance()->draw("bg", 0, 0, 640, 360);
    test->Draw();
    SDL_RenderPresent(Game::renderer);
}

void Game::Quit(){ 
    quit = true;
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    TextureManager::GetInstance()->clean();
    printf("Game cleaned!");
    SDL_Quit();
}