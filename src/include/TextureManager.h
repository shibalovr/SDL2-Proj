#ifndef TextureManager_h_
#define TextureManager_h_
#include "Game.h"

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* file);
};

#endif