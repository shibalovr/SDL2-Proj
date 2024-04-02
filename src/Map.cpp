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
            int col = id % 16;
            int row = id / 16;
            int x = j * TileSize;
            int y = i * TileSize;
            TextureManager::GetInstance()->drawTex(m_TileSet, row, col, x, y, TileSetSize, TileSetSize);
            j++;
        }
        i++;
    }
    mapFile.close();
    // m_MapLayers.insert(std::make_pair(mapLayerID, map));
    // printf("Map loaded!\n");
}

// void Map::DrawMapLayer(std::vector<std::vector<int>>  layer) {
//     for (unsigned int i = 0; i < layer.size(); i++) { // column
//         for (unsigned int j = 0; j < layer[i].size(); j++) { // row
//             if (layer[i][j] < 0) continue; 
//             SDL_Rect src, dist;
//             int col = layer[i][j] % 16;
//             int row = layer[i][j] / 16;
//             int x = j * 16;
//             int y = i * 16;
//             TextureManager::GetInstance()->drawTex(m_TileSet, row, col, x, y, 16, 16);
//         }
//     }
// }



// void Map::DrawMap() {
//     for (auto it = m_MapLayers.begin(); it != m_MapLayers.end(); it++) {
//         DrawMapLayer(it->second);
//     }
// }

void Map::Clean() {
    m_MapLayers.clear();
}