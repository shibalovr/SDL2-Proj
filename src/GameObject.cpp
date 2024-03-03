#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y) {
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x, ypos = y;
}

GameObject::~GameObject(){}

void GameObject::Update() {
    xpos++, ypos++;
    srcR.x = 0, srcR.y = 0; // it doesn't matter 
    srcR.w = 32;
    srcR.h = 48;

    int scale = 3;
    distR.x = xpos;
    distR.y = ypos;
    distR.h = srcR.h*scale;
    distR.w = srcR.w*scale;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &distR);
}