#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <Sea/Renderer/Renderer.hpp>
#include <Sea/Common/CommonType.hpp>
#include <Sea/Core/Context.hpp>

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
		virtual void Swap() abstract;
		inline RendererPtr GetRenderer() { return m_renderer; }

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
		bool m_isOpen = true;
		u32 m_width, m_height;
		std::string m_title;
		SDL_Window* m_handle;
		RendererPtr m_renderer;
		Context m_context;
	};
}
