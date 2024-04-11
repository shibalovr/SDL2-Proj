#pragma once

#ifndef NINJA_H
#define NINJA_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collision.h"
#include "HitBox.h"

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
        inline SDL_Rect getHitBox() {return m_HitBox->Get();}
        void Draw();
        void Update(float dt);
        void Clean();
    private:
        Direction curDirection = DOWN; 
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        HitBox* m_HitBox; // currently it is the wall hit box, add more hitbox for enemy, item,...
        Point m_lastSafePosition;

};

#endif