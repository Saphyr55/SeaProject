#pragma once

#include <SDL2/SDL.h>

#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/Game.hpp"
#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea
{
    struct Clock
    {
        const f32 TargetDelta = 1.5f;
        f32 Now = 0;
        f32 Last = 0;
        f32 Delta = 0;

        void StartTick(Game& game)
        {
            Now = SDL_GetTicks();
            Delta = (Now - Last) * (game.GetFPS()/1000);
        }

        void EndTick()
        {
			Last = Now;
        }

        f32 GetTicks()
        {
            return SDL_GetTicks();
        }

    };
}
