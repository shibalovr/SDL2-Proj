#include "Menu.h"

Menu* Menu::s_Instance = nullptr;

Menu* Menu::getInstance() {
    if (s_Instance == nullptr) {
        s_Instance = new Menu();
    } 
    return s_Instance;
}

void Menu::update() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (p_isExpand) {
        if (x <= p_OriginX-p_Width*p_scale/2 ||  x >= p_OriginX+p_Width*p_scale/2 
            || y <= p_OriginY - p_Height*p_scale/2 || y >= p_OriginY + p_Height*p_scale/2) {
                p_isExpand = false;
                p_scale = 1;
        }
    } else {
        if (x <= p_OriginX-p_Width*p_scale/2 ||  x >= p_OriginX+p_Width*p_scale/2 
            || y <= p_OriginY - p_Height*p_scale/2 || y >= p_OriginY + p_Height*p_scale/2) {
                p_isExpand = false;
                p_scale = 1;
        } else {
            p_isExpand = true;
            p_scale = 1.25;
        }
    }

    if (q_isExpand) {
        if (x <= q_OriginX-q_Width*q_scale/2 ||  x >= q_OriginX+q_Width*q_scale/2 
            || y <= q_OriginY - q_Height*q_scale/2 || y >= q_OriginY + q_Height*q_scale/2) {
                q_isExpand = false;
                q_scale = 1;
        }
    } else {
        if (x <= q_OriginX-q_Width*q_scale/2 ||  x >= q_OriginX+q_Width*q_scale/2 
            || y <= q_OriginY - q_Height*q_scale/2 || y >= q_OriginY + q_Height*q_scale/2) {
                q_isExpand = false;
                q_scale = 1;
        } else {
            q_isExpand = true;
            q_scale = 1.25;
        }
    }
}

void Menu::load() {
    TextureManager::GetInstance()->Load("play", "assets/menu/Play.png");
    TextureManager::GetInstance()->Load("quit", "assets/menu/Quit.png");
    TextureManager::GetInstance()->Load("resume", "assets/menu/Resume.png");
    TextureManager::GetInstance()->Load("bg", "assets/menu/bg.png");
    menu_musik = SoundManager::GetInstances()->LoadMusic("assets/sound/menu_loop.wav");
}

void Menu::PlayMenuMusic() {
    SoundManager::GetInstances()->PlayMusic(menu_musik);
}

void Menu::handleEvents() {
    Input::getInstance()->Listen();
}

void Menu::render() {
    SDL_RenderClear(Game::renderer);
    TextureManager::GetInstance()->draw("bg", 0, 0, 1200, 800);
    TextureManager::GetInstance()->drawScale("play", p_OriginX, p_OriginY, p_Width, p_Height, p_scale);
    TextureManager::GetInstance()->drawScale("quit", q_OriginX, q_OriginY, q_Width, q_Height, q_scale);
    SDL_RenderPresent(Game::renderer);
}

void Menu::MouseDown() {
    if (p_isExpand) {
        Menu::getInstance()->isMenu = false;
        SoundManager::GetInstances()->PlayChunk("press");
    } else if (q_isExpand) {
        Menu::getInstance()->isMenu = false;
        Game::getInstance()->quit = true;
        SoundManager::GetInstances()->PlayChunk("press");
    }
}

void Menu::clean() {
    if (menu_musik != nullptr) {
        Mix_FreeMusic(menu_musik);
    }
}