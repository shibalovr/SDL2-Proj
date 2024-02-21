#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDl2/SDL_image.h>


class Game{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    
    bool running();
    static SDL_Renderer* renderer;
private:
    bool isRunning;
    SDL_Window* window;
};



#endif /* Game_hpp */