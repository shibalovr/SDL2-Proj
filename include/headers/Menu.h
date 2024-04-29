#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Input.h"

class Menu {
    public:
        static Menu* getInstance();
        void handleEvents();
        void render();
        void update();
        void load();
        void MouseDown();

        bool isMenu;
    private:
        ~Menu() {
            delete s_Instance;
        }

        int p_OriginX, p_OriginY, p_Width, p_Height;
        int q_OriginX, q_OriginY, q_Width, q_Height;
        bool p_isExpand, q_isExpand;
        float p_scale, q_scale;
        Menu(){
            isMenu = _CMP_TRUE_UQ;
            p_scale = 1, q_scale = 1;
            p_OriginX = 600, p_OriginY = 500, p_Width = 300, p_Height = 100;
            q_OriginX = 600, q_OriginY = 650, q_Width = 300, q_Height = 100;
            p_isExpand = false;
            q_isExpand = false;
        }
        static Menu* s_Instance;       
};

#endif
