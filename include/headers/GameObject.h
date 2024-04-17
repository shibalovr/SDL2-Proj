#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Game.h"
#include <string>
#include "Point.h"


struct Properties {
    public:
        Properties(std::string TextureId, int x, int y, int width, int height,int scalar, SDL_RendererFlip Flip = SDL_FLIP_NONE) {
            X = x;
            Y = y;
            m_TextureId = TextureId;
            flip = Flip;
            m_width = width;
            m_height = height;
            m_scalar = scalar;
        }

    public:
        float X, Y;
        std::string m_TextureId;
        SDL_RendererFlip flip;
        int m_width, m_height;
        int m_scalar;
};

class GameObject
{
    public:
        ~GameObject() {
            delete m_Transform;
            delete m_Origin;
        }
        GameObject(Properties* props){
            m_Transform = new Transform(props->X, props->Y);
            float px = props->X + props->m_width/2;
            float py = props->Y + props->m_height/2;
            m_Origin = new Point(px, py);
            m_TextureId = props->m_TextureId;
            m_Width = props->m_width;
            m_Height = props->m_height;
            m_Flip = props->flip;
            m_scalar = props->m_scalar;
        }
        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;

    protected:
        int m_scalar;
        Point* m_Origin;
        Transform* m_Transform;
        int m_Width, m_Height;
        std::string m_TextureId;
        SDL_RendererFlip m_Flip;
};

#endif