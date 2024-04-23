#include "TextureManager.h"

TextureManager* TextureManager::s_Instance = nullptr;

TextureManager::TextureManager(){}

TextureManager* TextureManager::GetInstance() {
    if (!s_Instance) {
        s_Instance = new TextureManager();
    }
    return s_Instance;
}

bool TextureManager::Load(std::string id, std::string file) {
    SDL_Surface* tmpSurface = IMG_Load(file.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    if (tex == NULL) {
        printf("cannot create tex!\n");
        return false;
    }
    SDL_FreeSurface(tmpSurface);
    m_TextureMap[id] = tex;
    return true;
}

void TextureManager::drop(std::string id) {
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::clean() {
    auto it = m_TextureMap.begin();
    while(it!= m_TextureMap.end()) {
        SDL_DestroyTexture(it->second);
        it++;
    }
    m_TextureMap.clear();
}

void TextureManager::drawTex(SDL_Texture* tex, int row, int col,  int x, int y, int width, int height ,SDL_RendererFlip flip){
    SDL_Rect src = {col*16, row*16, width, height};
    Vector2d cam = Camera::GetInstance()->getPosition();
    SDL_Rect dist = {int(x - cam.x), int(y - cam.y), 40, 40};
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dist, 0, NULL, flip);
}


void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {0,0, width, height};
    SDL_Rect disRect = {x,y, width, height};
    SDL_RenderCopyEx(Game::renderer, m_TextureMap[id], &srcRect, &disRect, 0, NULL, flip);
}

void TextureManager::drawframe(std::string id, int x, int y, int width, int height, int row, int frame, int scalar, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {width * frame, height * row , width, height}; // xpos  = width*frame, y pos = height * row
    Vector2d cam = Camera::GetInstance()->getPosition();
    SDL_Rect disRect = {int(x-cam.x), int(y-cam.y), width*scalar, height*scalar};
    SDL_RenderCopyEx(Game::renderer, m_TextureMap[id], &srcRect, &disRect, 0, NULL, flip);
}

void TextureManager::drawHitBox(HitBox* Hbox) {
    Vector2d cam = Camera::GetInstance()->getPosition();
    SDL_Rect box = Hbox->Get();
    box.x -= cam.x;
    box.y -= cam.y;

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &box);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}
