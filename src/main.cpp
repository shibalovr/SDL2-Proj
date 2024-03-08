#include "Game.h"

Game *game = NULL;


int main(int argc, char* arg[]) {
    game = new Game();
    game->init("Anh Manh dep trai vai loz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0);
    
    while (!game->Quit()) {
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    
    return 0;
}
