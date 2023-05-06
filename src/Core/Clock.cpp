#include "Sea/Core/Clock.hpp"

namespace Sea
{
    
    void Clock::Start()
    {
        m_startFPS = SDL_GetPerformanceCounter();
        Now = GetTicks();
        Delta = (Now - Last) * (GetFPS() / 1000);
    }

    void Clock::End()
    {
        m_endFPS = SDL_GetPerformanceCounter();
        m_fps = 1 / ((m_endFPS - m_startFPS) / (f32) SDL_GetPerformanceFrequency());
        Last = Now;
    }

}