#pragma once

#ifndef NINJA_H
#define NINJA_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"


class Ninja : public Character
{
    public:
        Ninja(Properties* props);

        virtual void Draw();
        virtual void Update();
        virtual void Clean();

    private:
        // int m_Row, m_Frame, m_FrameCount;
        // int m_aniSpeed;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
};

#endif