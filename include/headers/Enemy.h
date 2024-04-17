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
        void SetMovingArea(int x, int y, int w, int h) {
            m_MovingArea.x = x;
            m_MovingArea.y = y;
            m_MovingArea.w = w;
            m_MovingArea.h = h;
        } 
        void Draw();
        void Update(float dt);
        void Clean();
    private:
        HitBox* m_HitBox;
        bool m_isDead;
        SDL_Rect m_MovingArea = {720, 920, 500, 500};
        Point m_LastSafePosition;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
};



#endif