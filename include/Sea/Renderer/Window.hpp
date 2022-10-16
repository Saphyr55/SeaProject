#pragma once

#include <string>
#include <iostream>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <Sea/Renderer/Renderer.hpp>

namespace Sea
{	
	using RendererPtr = std::shared_ptr<Renderer>;

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
		RendererPtr m_rendererPtr;
		bool m_isOpen = true;
		SDL_Window* m_handle;
		std::string m_title;
		std::uint32_t m_width, m_height;
	};
}
