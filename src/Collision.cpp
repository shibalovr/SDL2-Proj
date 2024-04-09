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