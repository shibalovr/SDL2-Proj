#pragma once

#include <SDL.h>

#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60.0f;

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
            m_DeltaTime = 1/TARGET_FPS;
        }
        ~Timer() {
            delete s_Instance;
        }
        static Timer* s_Instance;
        float m_DeltaTime;
        float m_LastTime;
};


#endif