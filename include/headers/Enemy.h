#pragma once

#ifndef ENEMY_H
#define ENEMY_H

class GameObject;
class RigidBody;
class HitBox;
class Point;

#include "HitBox.h"
#include "Point.h"
#include "Collision.h"
#include "RigidBody.h"
#include "Animation.h"

#include "GameObject.h"

class Enemy : public GameObject
{
    public: 
        Enemy(Properties* props);
        inline Point* GetOrigin() {return m_Origin;}
        inline SDL_Rect GetHitBox() {return m_HitBox->Get();}
        void SetMovingArea(int Range, int speed) {
            m_MoveRangeX = Range;
            m_speedX = speed;
        } 
        void Draw();
        void Update(float dt);
        void Clean();
    private:
        HitBox* m_HitBox;
        bool m_isDead;
        int m_MoveRangeX, m_speedX, x;
        // SDL_Rect m_MovingArea;
        Point m_LastSafePosition;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
};



#endif