#include "Game.h"


int main(int argc, char* arg[]) {
    Game::getInstance()->init("Anh Manh dep trai vai loz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0);
    while(Game::getInstance()->menu) {
        Menu::getInstance()->handleEvents();
        Menu::getInstance()->update();
        Menu::getInstance()->render();
    }
    while (!Game::getInstance()->quit) {
        Game::getInstance()->handleEvents();
        Game::getInstance()->update();
        Game::getInstance()->render();
        Timer::getInstance()->Tick();
    }
    Game::getInstance()->clean();
    
    return 0;
}
