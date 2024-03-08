#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <algorithm>
#include <map>
#include "TextureManager.h"
#include "Vector2d.h"
#include "Transform.h"
#include "Ninja.h"

const int WIDTH = 700;
const int HEIGHT = 900;

class Game{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    
    bool Quit();
    static SDL_Renderer* renderer;
    int cnt = 0;
    bool quit;
private:
    
    
    SDL_Window* window;
};



#endif /* Game_hpp */