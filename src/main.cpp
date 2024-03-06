#include "Game.h"

Game *game = NULL;


int main(int argc, char* arg[]) {
    game = new Game();
    Transform tf(1,3);
    tf.log();
    game->init("Anh Manh dep trai vai loz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0);
    
    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    
    return 0;
}
