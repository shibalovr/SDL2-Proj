#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <SDL.h>


class Animation {
    public:
        Animation () {}

        void Update();

        void Draw(float x, float y, int width, int height);

        void setProps(std::string TextureId, int spriteRow, int frameCount, int anim_speed, SDL_RendererFlip flip=SDL_FLIP_NONE);
    private:
        int m_SpriteRow, m_FrameCount;
        int m_AnimSpeed, m_SpriteFrame;

        std::string m_TextureId;
        SDL_RendererFlip m_Flip;
};

#endif