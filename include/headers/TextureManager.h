#ifndef TextureManager_h_
#define TextureManager_h_
#include "Game.h"
#include "HitBox.h"


class TextureManager {
public:
    static TextureManager* GetInstance();

    bool Load(std::string id, std::string file);

    void drop(std::string id);

    void clean();
    void drawTex(SDL_Texture* tex,int row, int col, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE);

    void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE);

    void drawHitBox(HitBox* Hbox);

    void drawframe(std::string id, int x, int y, int width, int height, int row, int frame, int scalar, SDL_RendererFlip flip=SDL_FLIP_NONE);
private:
    TextureManager();   
    ~TextureManager() {
        delete s_Instance;
    }
    std::map<std::string, SDL_Texture*> m_TextureMap;
    static TextureManager* s_Instance;
};

#endif