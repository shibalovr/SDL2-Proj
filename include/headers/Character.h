#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

class GameObject;
class Point;
class RigidBody;
class HitBox;

#include "Animation.h"
#include "RigidBody.h"
#include "Collision.h"
#include "HitBox.h"
#include "Sound.h"
#include "Game.h"

#include "GameObject.h"

#define MAX_FALL_FORCE 30

#define JUMP_TIME 50
#define FALL_TIME 50
#define DEAD_TIME 100

#define JUMP_FORCE 10.0f
#define FALL_FORCE 10.0f

#define MAX_JUMPTIME 50

enum Direction {
    NONE,
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
        void Draw();
        void Update(float dt);
        void Clean();
    private:
        bool m_isCrouching, m_isFalling;
        bool m_isCheatMode;
        bool m_isGrounded, m_isJumping;
        float m_JumpTime, m_FallTime, m_DeadTime;
        float m_FallForce;
        bool m_jumpMusic, m_fallMusic;
        bool m_isBounce, m_isDead;
        Direction curDirection = RIGHT; 
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        HitBox* m_TopHB; 
        HitBox* m_MidHB;
        HitBox* m_BotHB;
        SDL_Rect m_PrincessHB = {800, 300, 64, 56};
        Point m_lastSafePosition;
};

#endif