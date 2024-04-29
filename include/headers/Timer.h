#pragma once

#include <SDL.h>

#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60.0f;
const float TARGET_DELTATIME = 5.0f;


class Timer {
    public:
        static Timer* getInstance() {
            if (!s_Instance) {
                s_Instance = new Timer();
            }
            return s_Instance;
        }
        void Tick();

        inline float getDeltaTime() {
            return m_DeltaTime*10;
        }

    private:
        Timer() {
            m_DeltaTime = 0.0f;
            m_LastTime = SDL_GetTicks();
        }
        ~Timer() {
            delete s_Instance;
        }
        static Timer* s_Instance;
        float m_DeltaTime;
        float m_LastTime;
};


#endif