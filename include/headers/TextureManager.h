#ifndef TextureManager_h_
#define TextureManager_h_
#include "Game.h"


class TextureManager {
public:
    static TextureManager* GetInstance();

    bool Load(std::string id, std::string file);

    void drop(std::string id);

    void clean();
    
    void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE);

    void drawframe(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);
private:
    TextureManager();   
    std::map<std::string, SDL_Texture*> m_TextureMap;
    static TextureManager* s_Instance;
};

#endif