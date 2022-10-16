#pragma once

#include <string>
#include <iostream>
#include <stdint.h>
#include <SDL2/SDL.h>

namespace Sea
{
	class Window
	{
	public:
		void Hide();
		void Show();
		void Close();
		bool IsOpen();
		bool IsClosed();

	public:
		Window(std::string title, std::uint32_t width, std::uint32_t height);
		~Window();

	protected:
		SDL_Window* m_handle;
		bool m_isOpen = true;
		std::string m_title;
		std::uint32_t m_width, m_height;
	};
}
