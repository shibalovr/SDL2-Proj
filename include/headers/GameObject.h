#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Game.h>
#include <IObject.h>

struct Properties {
    public:
        Properties(std::string TextureId, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
            X = x;
            Y = y;
            o_TextureId = TextureId;
            Flip = flip;
            o_width = width;
            o_height = height;
        }

    public:
        float X, Y;
        std::string o_TextureId;
        SDL_RendererFlip Flip;
        int o_width, o_height;
};

class GameObject : public IObject
{
    public:
        GameObject(Properties* props) {
            o_Transform = new Transform(props->X, props->Y);
            o_Width = props->o_width;
            o_Height = props->o_height;
            o_TextureId = props->o_TextureId;
            o_Flip = props->Flip;
        }

        virtual void Draw() = 0;
        virtual void Update() = 0;
        virtual void Clean() = 0;

    protected:
        Transform* o_Transform;
        int o_Width, o_Height;
        std::string o_TextureId;
        SDL_RendererFlip o_Flip;
};

#endif