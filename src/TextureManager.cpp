#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* file) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}