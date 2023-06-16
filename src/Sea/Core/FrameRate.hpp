#pragma once

#include <SDL2/SDL.h>

#include "Sea/Core/Common.hpp"

namespace Sea
{
	class FrameRate 
	{
	friend class Clock;

	public:
		inline f32 GetFPS() { return m_fps; }

		FrameRate() = default;
		~FrameRate() = default;
	
	private:
		void Start() { m_startFPS = SDL_GetPerformanceCounter(); }
		void End() { m_endFPS = SDL_GetPerformanceCounter(); }
		void Calculate() { m_fps = 1 / ((m_endFPS - m_startFPS) / (f32)SDL_GetPerformanceFrequency()); }

	private:
		f32 m_startFPS{};
		f32 m_endFPS{};
		f32 m_fps{};

	};
}