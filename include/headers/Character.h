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

#include "GameObject.h"

#define ATTACK_TIME 5.0f
#define ROLL_TIME 6.0f

#define WALKFORCE 500.0f
#define ROLLFORCE 1500.00f

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