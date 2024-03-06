#include "Game.h"


SDL_Renderer* Game::renderer = nullptr;

TextureManager* TextureManager::TM = nullptr;

Game::Game(){}
Game::~Game(){}

Ninja* test = nullptr;

void Game::init(const char* title, int xpos, int ypos, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
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
        isRunning = true;
    } else {
        isRunning = false;
    }
    TextureManager::TM = new TextureManager();
    if (TextureManager::TM == nullptr) {
        printf("Cannot create texture manager!\n");
        return;
    }
    TextureManager::TM->Load("bg", "assets/backgrounds/bg.png");
    TextureManager::TM->Load("ninja", "assets/sprites/character.png");
    test = new Ninja(new Properties("ninja", 100, 200, 48, 48));
}


void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }

}

void Game::update() {  
    test->Update();
}

void Game::render() {
    SDL_RenderClear(Game::renderer);
    
    TextureManager::TM->draw("bg", 0, 0, 640, 350);
    test->Draw();
    SDL_RenderPresent(Game::renderer);
}

bool Game::running() {
    return isRunning;
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    TextureManager::TM->clean();
    printf("Game cleaned!");
    SDL_Quit();
}