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
		friend class Application;
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
		void SetTitle(std::string title);
		void SetMousePostion(f32 x, f32 y);
		void SetMouseOnMiddlePosistion();
		void GrapMouse();
		void UngrapMouse();
		inline Event& GetEvent() { m_event; }
		inline SDL_Window* GetHandle() { return m_handle; }
		inline Properties GetProperties() { return m_properties; }
		inline const Renderer& GetRenderer() { return *m_renderer; }

	private:
		void CreateEvent();
		void Update();

	public:
		struct Properties
		{
			ContextType Context = ContextType::OpenGL;
			std::string Title = "No Title";
			std::string FileIcon = "";
			u32 Width = 1080;
			u32 Height = 720;
			bool Resizable = false;
			bool Fullscreen = false;

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

	using WindowPtr = std::shared_ptr<Window>;

}
