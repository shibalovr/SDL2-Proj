#pragma once

#ifndef NINJA_H
#define NINJA_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

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
        }
        inline Point* GetOrigin() {return m_Origin;}
        void Draw();
        void Update(float dt);
        void Clean();
    private:
        Direction curDirection = DOWN; 
        Animation* m_Animation;
        RigidBody* m_RigidBody;
};

#endif