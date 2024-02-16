#include "Game.cpp"

Game *game = NULL;


int main(int argc, char* arg[]) {
    game = new Game();
    game->init("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }


    game->clean();

    return 0;
}
