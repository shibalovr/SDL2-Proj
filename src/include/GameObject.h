#ifndef GameObject_h_
#define GameObject_h_
#include "Game.h"


class GameObject {
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();


    void Update();
    void Render();
private:

    int xpos, ypos;
    SDL_Texture* objTexture;
    SDL_Rect srcR, distR;

};

#endif

