#include <Timer.h>

Timer* Timer::s_Instance = nullptr;

void Timer::Tick() {
    m_DeltaTime = (SDL_GetTicks() - m_LastTime) /1000.0f;
    
    float frameDelay = 1.0f/TARGET_FPS;
    if (m_DeltaTime < frameDelay) {
        SDL_Delay((frameDelay - m_DeltaTime) * 1000);
    } 
    m_DeltaTime = frameDelay;
    m_LastTime = SDL_GetTicks();
}