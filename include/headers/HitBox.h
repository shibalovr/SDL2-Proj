#ifndef HITBOX_H
#define HITBOX_H

#include <SDL.h>

class HitBox {
    public:
        inline SDL_Rect Get() {return m_Box;}
        inline void SetBuffer(int x, int y, int w, int h) {
            m_Buffer = {x, y, w, h};
        }
        void Set(int x, int y, int w, int h, int scalar)  {
            m_Box = {
                x - m_Buffer.x,
                y - m_Buffer.y,
                w * scalar - m_Buffer.w,
                h * scalar - m_Buffer.h
            };
        }
    private:
        SDL_Rect m_Box;
        SDL_Rect m_Buffer;
};

#endif