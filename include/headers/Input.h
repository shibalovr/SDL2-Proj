#pragma once

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <Game.h>

class Input {
    public:
        static Input* getInstance();

        SDL_Event e;
        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        
    private:
        Input();
        
        void KeyUp();
        void KeyDown();

        const Uint8* m_KeyStates;
        static Input* s_Instance;
};

#endif