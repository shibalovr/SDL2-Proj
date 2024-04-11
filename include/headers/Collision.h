#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include "Point.h"
#include "Map.h"


class ColHandler {
    public:
        static ColHandler* GetInstance();
        void LoadCollider(std::string path);
        bool CheckCollide(const SDL_Rect& rectA, const SDL_Rect& rectB);

        bool CheckCollideMap(const SDL_Rect& rectA, int twidth, int theight);
    private:
        ColHandler(){}
        ~ColHandler() {
            delete s_Instance;
        }
        static ColHandler* s_Instance;
        std::vector<Point> Collider;

};


#endif