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
    endMusic = false;
    win = false;
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

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0) {
            printf("Mixer created\n");
        }
    } else {
        quit = true;
    }
    TextureManager::GetInstance()->Load("idle", "assets/sprites/idle.png");
    TextureManager::GetInstance()->Load("walk", "assets/sprites/walk.png");
    TextureManager::GetInstance()->Load("crouch", "assets/sprites/crouch.png");
    TextureManager::GetInstance()->Load("jump_up", "assets/sprites/jump_up.png");
    TextureManager::GetInstance()->Load("jump_down", "assets/sprites/jump_down.png");
    TextureManager::GetInstance()->Load("bounce", "assets/sprites/bounce.png");
    TextureManager::GetInstance()->Load("princess", "assets/sprites/princess.png");
    TextureManager::GetInstance()->Load("dead", "assets/sprites/dead.png");;
    TextureManager::GetInstance()->Load("win", "assets/win.png");
    SoundManager::GetInstances()->LoadChunk("jump", "assets/sound/jump.wav");
    SoundManager::GetInstances()->LoadChunk("bump", "assets/sound/bump.wav");
    SoundManager::GetInstances()->LoadChunk("land", "assets/sound/land.wav");
    SoundManager::GetInstances()->LoadChunk("press", "assets/sound/press.wav");
    charac = new Character(new Properties("idle", 500, 3890, 32, 28, 2));
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
    Camera::GetInstance()->Update();
}

void Game::render() {
    SDL_RenderClear(Game::renderer);
    Map::GetInstance()->LoadMap(0, "assets/map/bg_bg.csv");
    Map::GetInstance()->LoadMap(1, "assets/map/bg_wall.csv");
    TextureManager::GetInstance()->drawframe("princess", 800, 300, 32, 28, 0, 0, 2);
    charac->Draw();
    if (Game::getInstance()->win) {
        if (endMusic == false) {
            Mix_Music* win = SoundManager::GetInstances()->LoadMusic("assets/sound/ending.wav");
            SoundManager::GetInstances()->PlayMusic(win);
            endMusic == true;
        }
        TextureManager::GetInstance()->drawScale("win", 600, 300, 1501, 699, 0.5);
    }
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
    Mix_Quit();
    SDL_Quit();
}