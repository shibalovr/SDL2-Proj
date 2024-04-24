#include <Input.h>

Input* Input::s_Instance = nullptr;

Input::Input(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

Input* Input::getInstance(){
    if (!s_Instance) {
        s_Instance = new Input();
    }

    return s_Instance;
}

void Input::Listen() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT: 
                Game::getInstance()->Quit();
                Menu::getInstance()->isMenu = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Menu::getInstance()->MouseDown();
                break;
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