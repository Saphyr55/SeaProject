#pragma once

#include <memory>
#include <vector>

#include "Sea/Input/Input.hpp"

#include <SDL2/SDL.h>

namespace Sea
{	
	class Window;

	class EventHandler final
	{
	friend class Input;

	public:
		EventHandler();
		void HandleEvent(Window& widow);
		void ClearEvent();

	private:
		bool mousefirst = true;
		bool mouseMotion = false;
		SDL_Event m_handle;
	};


}