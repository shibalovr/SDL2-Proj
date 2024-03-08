#pragma once

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <Game.h>

class Input {
    public:
        SDL_Event e;
        void Listen();
        bool GetKeyDown(SDL_Scancodekey);
        
    private:
        Input* getInput;
        
        Input(){};
        void KeyUp();
        void KeyDown();

        const Uint8* m_KeyStates;
};

#endif