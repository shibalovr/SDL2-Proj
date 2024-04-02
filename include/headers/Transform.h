#pragma once

#ifndef transform_h
#define transform_h

#include <Game.h>

class Transform {
    public:
        float x, y;
        Transform() {
            x = 0;
            y = 0;
        }
        
        Transform(float X = 0, float Y = 0) {
            x = X; 
            y = Y;
        }

        void log() {
            printf("%f %f\n", x, y);
        }
        inline void translateX(float X) {x += X;}
        inline void translateY(float Y) {y += Y;}
        inline void translate(Vector2d v) {
            x += v.x;
            y += v.y;
        }
    


};

#endif