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
        bool GetKeyUp(SDL_Scancode key);
        
    private:
        Input();
        ~Input() {
            delete m_KeyStates;
            delete s_Instance;
        }
        
        void KeyUp();
        void KeyDown();
        bool quit;
        const Uint8* m_KeyStates;
        static Input* s_Instance;
};

#endif