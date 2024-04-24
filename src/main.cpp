#include "Game.h"


int main(int argc, char* arg[]) {
    Game::getInstance()->init("Little dungeon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0);
    Menu::getInstance()->load();
    while(Menu::getInstance()->isMenu) {
        Menu::getInstance()->handleEvents();
        Menu::getInstance()->update();
        Menu::getInstance()->render();
    }
    while (!Game::getInstance()->quit) {
        Timer::getInstance()->Tick();
        Game::getInstance()->handleEvents();
        Game::getInstance()->update();
        Game::getInstance()->render();
    }
    Game::getInstance()->clean();
    
    return 0;
}
