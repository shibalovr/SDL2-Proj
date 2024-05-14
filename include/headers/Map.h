#ifndef MAP_H
#define MAP_H

#include "TextureManager.h"

class Map {
    public:
        static Map* GetInstance();
        void LoadTileSets(std::string path);

        void LoadMap(int mapLayersId, std::string path);

        void Clean();
    private:
        int TileSetSize = 8;
        int TileSize = 40;
        Map() ;
        ~Map() {
            delete s_Instance;
        }
        std::map<int, std::vector<std::vector<int>>> m_MapLayers;
        SDL_Texture* m_TileSet;
        static Map* s_Instance;
};



#endif