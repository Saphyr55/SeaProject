#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <Sea/Renderer/Renderer.hpp>
#include <Sea/Common/CommonType.hpp>
#include <Sea/Context.hpp>

namespace Sea
{	
	using RendererPtr = std::shared_ptr<Renderer>;

	struct WindowProperties
	{
		std::string title = "No Title";
		u32 width = 1080;
		u32	height = 720;
		ContextType context = ContextType::OpenGL;

		WindowProperties() = default;
		~WindowProperties() = default;
		WindowProperties(const WindowProperties&) = default;
		WindowProperties(WindowProperties&&) = default;
	};

	class Window
	{
	public:
		static std::shared_ptr<Window> Of(WindowProperties& properties);

		virtual void Run() abstract;

		void Hide();
		void Show();
		void Close();
		bool IsOpen();
		bool IsClosed();

		inline u32 GetWidth() { return m_width; }
		inline u32 GetHeight() { return m_height; }
		
	public:
		Window(WindowProperties& proterties);
		~Window();

	protected:
		Context m_context;
		bool m_isOpen = true;
		SDL_Window* m_handle;
		std::string m_title;
		u32 m_width, m_height;
	};
}
