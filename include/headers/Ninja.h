#pragma once

#ifndef NINJA_H
#define NINJA_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

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

        virtual void Draw();
        virtual void Update();
        virtual void Clean();

    private:
        Direction curDirection = DOWN; 
        Animation* m_Animation;
        RigidBody* m_RigidBody;
};

#endif