#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "Sea/Core/IWindow.hpp"

namespace Sea
{
	class GameWindow : public IWindow
	{
	public:
		GameWindow(std::string title, std::uint32_t width, std::uint32_t height);
		~GameWindow()
		{
			SDL_DestroyWindow(m_handle);
		}

		virtual void Hide()=0;
		virtual void Show()=0;

	protected:
		SDL_Window* m_handle;
	};

}