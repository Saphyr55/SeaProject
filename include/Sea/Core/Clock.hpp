#pragma once

#include <SDL2/SDL.h>

#include "Sea/Common/CommonType.hpp"

#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea
{

    struct Clock
    {

    public:
        Clock() { Last = GetTicks(); }
        ~Clock() = default;

    public:
        void Start();
        void End();
		inline f32 GetFPS() { return m_fps; }
		inline f32 GetTicks() { return SDL_GetTicks(); }

	public:
		f32 Now   = 0;
		f32 Last  = 0;
		f32 Delta = 0;

	private:
		f32 m_startFPS = 0;
		f32 m_endFPS   = 0;
		f32 m_fps      = 0;

    };
}
