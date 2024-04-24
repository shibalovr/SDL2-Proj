#include "Map.h"


Map* Map::s_Instance = nullptr;



Map* Map::GetInstance() {
    if (!s_Instance) {
        s_Instance = new Map();   
    }
    return s_Instance;
}

Map::Map(){}

void Map::LoadTileSets(std::string path) {
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    if (tex == nullptr) {
        printf("Error\n");
    } else {
        printf("Tile map loaded!\n");
    }

    SDL_FreeSurface(tmpSurface);
    m_TileSet = tex;
}

void Map::LoadMap(int mapLayerID, std::string path) {
    std::vector<std::vector<int>> map;
    std::ifstream mapFile(path);
    if (!mapFile.is_open()) {
        printf("Cannot load map\n");
        return;
    }
    std::string line;
    int i(0);
    while (std::getline(mapFile, line)) {
        int j(0);
        std::string cell;
        std::stringstream ss(line);
        while (getline(ss, cell, ',')) {
            int id = std::stoi(cell);
            if (id < 0) {
                j++;
                continue;
            }
            int col = id % 8;
            int row = id / 8;
            int x = j * TileSize;
            int y = i * TileSize;
            TextureManager::GetInstance()->drawTex(m_TileSet, row, col, x, y, TileSetSize, TileSetSize);
            j++;
        }
        i++;
    }
    mapFile.close();
}

void Map::Clean() {
    m_MapLayers.clear();
}