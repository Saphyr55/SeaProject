#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <Sea/Renderer/Renderer.hpp>
#include <Sea/Common/CommonType.hpp>
#include <Sea/Core/Context.hpp>
#include <Sea/Core/Input/Event.hpp>

namespace Sea
{	

	class Window
	{	
		friend class Engine;
		friend class Context;
		struct Properties;

	public:
		static std::shared_ptr<Window> Of(Window::Properties& properties);

		virtual void Run()=0;
		virtual void Swap()=0;
		virtual void UseVSync(bool use)=0;
		virtual void Viewport() = 0;
		virtual void Viewport(u32 h, u32 w) = 0;
		virtual void Viewport(u32 x, u32 y, u32 h, u32 w) = 0;

		void Hide();
		void Show();
		void Close();
		bool IsOpen();
		bool IsClosed();
		void SetSize(f32 w, f32 h);
		void SetResizable(bool resizable);
		void WrapMouse(f32 x, f32 y);
		inline SDL_Window* GetHandle() { return m_handle; }
		inline Properties GetProperties() { return m_properties; }
		inline const Renderer& GetRenderer() { return *m_renderer; }

	private:
		void CreateEvent();
		void Update();

	public:
		struct Properties
		{
			ContextType context = ContextType::OpenGL;
			std::string title = "No Title";
			std::string fileIcon = "";
			u32 width = 1080;
			u32 height = 720;
			bool resizable = false;
			bool fullscreen = false;

			Properties() = default;
			Properties(const Properties&) = default;
			Properties(Properties&&) = default;
			~Properties() = default;
		};

	public:
		Window(Window::Properties& proterties);
		Window(const Window &) = default;
		Window(Window &&) = default;
		~Window();

	protected:
		bool m_isOpen = true;
		SDL_Window* m_handle;
		Properties m_properties;
		std::shared_ptr<const Renderer> m_renderer;
		std::shared_ptr<Context> m_contextPtr;
		std::shared_ptr<Event> m_event;
	
	};
}
