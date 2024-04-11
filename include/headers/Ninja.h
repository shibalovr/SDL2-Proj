#pragma once

#ifndef NINJA_H
#define NINJA_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
// #include "HitBox.h"

enum AnimationState {
    ANIMATION_PLAYING,
    ANIMATION_STOPPED
};

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Ninja : public Character
{
    public:
        Ninja(Properties* props);
        ~Ninja() {
            delete m_Animation;
            delete m_RigidBody;
            // delete m_HitBox;
        }
        inline Point* GetOrigin() {return m_Origin;}
        inline SDL_Rect GetRect() {
            SDL_Rect tmp;
            tmp.x = m_Transform->x;
            tmp.y = m_Transform->y;
            tmp.w = m_Width;
            tmp.h = m_Height;
            return tmp;
        }
        void Draw();
        void Update(float dt);
        void Clean();
    private:
        Direction curDirection = DOWN; 
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        // int z;
};

#endif