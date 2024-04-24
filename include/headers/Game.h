#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include "TextureManager.h"
#include "Vector2d.h"
#include "Transform.h"
#include "Character.h"
#include "Input.h"
#include "Timer.h"
#include "Map.h"
#include "Camera.h"
#include "Collision.h"
#include "Menu.h"


const int WIDTH = 1200;
const int HEIGHT = 800;

class Game{
public:
    static Game* getInstance();

    void init(const char* title, int xpos, int ypos, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();    
    void Quit();
    static SDL_Renderer* renderer;
    int cnt = 0;
    bool quit;
    bool menu;
private:
    Game();
    ~Game() {
        delete s_Instance;
    }
    static Game* s_Instance;
    SDL_Window* window;
};



#endif /* Game_hpp */