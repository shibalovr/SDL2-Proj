#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* player;
GameObject* flame;

SDL_Renderer* Game::renderer = nullptr;

Game::Game(){}
Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        printf("Subsystems Initialised!\n");

        window = SDL_CreateWindow(title, ypos, xpos, width, height, flags);
        if (window) {
            printf("Window created!\n");
        }

        Game::renderer = SDL_CreateRenderer(window, -1, 0);
        if (Game::renderer) {
            SDL_SetRenderDrawColor(Game::renderer, 104, 176, 40, 255);
            printf("Renderer created\n");
        }
        isRunning = true;
    } else {
        isRunning = false;
    }
    player = new GameObject("assets/player.png", 0, 0);
    flame = new GameObject("assets/flame.png" ,600, 0);
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
    player->Update(); 
    flame->Update();
}

void Game::render() {
    SDL_RenderClear(Game::renderer);
    player->Render();
    flame->Render();
    SDL_RenderPresent(Game::renderer);
}

bool Game::running() {
    return isRunning;
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    printf("Game cleaned!");
    SDL_Quit();
}