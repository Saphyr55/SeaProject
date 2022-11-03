#pragma once

#include <SDL2/SDL.h>

#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/FrameRate.hpp"

#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea
{
    struct Clock
    {
        f32 Now = 0;
        f32 Last = 0;
        f32 Delta = 0;
          
        Clock() { Last = GetTicks(); }
        ~Clock()=default;

        void Start(FrameRate& frameRate)
        {
			frameRate.Start();
            Now = SDL_GetTicks();
            Delta = (Now - Last) * (frameRate.GetFPS() / 1000);
        }

        void End(FrameRate& frameRate)
        {
			frameRate.End();
            frameRate.Calculate();
            Last = Now;
        }

    private:
        f32 GetTicks()
        {
            return SDL_GetTicks();
        }

    };
}
