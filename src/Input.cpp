#include <Input.h>

Input::Input() {
    
}

void Input::Listen() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                quit = true;
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;
        }
    }
}

void Input::KeyDown() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}   

void Input::KeyUp() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

bool Input::GetKeyDown(SDL_Scancode key) {
    if (m_KeyStates[key] == 1) {
        return true;
    } 
    return false;
}