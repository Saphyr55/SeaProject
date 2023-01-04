#pragma once

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "Sea/Core/Application.hpp"
#include "Sea/Renderer/Window.hpp"

namespace Sea
{	
	class EventHandler final
	{
	friend class Input;

	public:
		EventHandler(Window& window) : m_window(&window) { }
		void HandleEvent();
		void ClearEvent();

	private:
		bool mousefirst = true;
		bool mouseMotion = false;
		SDL_Event m_handle;
		Window* m_window;
	};


}