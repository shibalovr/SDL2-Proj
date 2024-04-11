#include "Collision.h"

ColHandler* ColHandler::s_Instance = nullptr;

void ColHandler::LoadCollider(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        printf("Cannot load Collider map\n");
        return;
    } 

    int i(0);
    std::string line;
    while (getline(file, line)) {
        int j(0);
        std::stringstream ss(line);
        std::string cell;
        while (getline(ss, cell, ',')) {
            int id = std::stoi(cell);
            if (id > 0) {
                Point tmp(j, i);
                Collider.push_back(tmp);
            }
            j++;
        }
        i++;
    }
    
    for (Point x : Collider) {
        x.Log();
    }
}

ColHandler* ColHandler::GetInstance() {
    if (s_Instance == nullptr) {
        s_Instance = new ColHandler;
    }
    return s_Instance;
}


bool ColHandler::CheckCollideMap(const SDL_Rect& rectA,int twidth, int theight) {
    for (Point p : Collider) { // Point p.x = col, p.y = row;
        SDL_Rect tmp;
        tmp.x = p.x * twidth;
        tmp.y = p.y * theight;
        tmp.w = twidth;
        tmp.h = theight;
        if (CheckCollide(rectA, tmp)) return true;
    }
    return false;
}

bool ColHandler::CheckCollide(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    if (
        rectA.x + rectA.w >= rectB.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.x + rectB.w >= rectA.x &&
        rectB.y + rectB.h >= rectA.y
    ) {
        return true;
    } else {
        return false;
    }
}