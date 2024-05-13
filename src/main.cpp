#include "Game.h"


int main(int argc, char* arg[]) {
    Game::getInstance()->init("Jump king", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0);
    Menu::getInstance()->load();
    Menu::getInstance()->PlayMenuMusic();
    while(Menu::getInstance()->isMenu) {
        Menu::getInstance()->handleEvents();
        Menu::getInstance()->update();
        Menu::getInstance()->render();
    }
    Menu::getInstance()->clean();
    while (!Game::getInstance()->quit) {
        Timer::getInstance()->Tick();
        Game::getInstance()->handleEvents();
        if (!Game::getInstance()->win) {
            Game::getInstance()->update();
        }
        Game::getInstance()->render();
    }

    Game::getInstance()->clean();
    
    return 0;
}
