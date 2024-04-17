#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collision.h"
#include "HitBox.h"

#define ATTACK_TIME 30.0f
#define ROLL_TIME 30.0f

#define WALKFORCE 1500.0f
#define ROLLFORCE 4000.00f

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

class Character : public GameObject
{
    public:
        Character(Properties* props);
        ~Character() {
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
        bool m_Shoot;
        bool m_isWalk, m_isRoll;
        bool m_isAttack;

        float m_RollTime;
        float m_AttackTime;
        Direction curDirection = DOWN; 
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        HitBox* m_HitBox; // currently it is the wall hit box, add more hitbox for enemy, item,...
        Point m_lastSafePosition;
};

#endif