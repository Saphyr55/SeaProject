#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "Sea/Graphics/Rendering/Renderer.hpp"
#include "Sea/Core/Common.hpp"
#include "Sea/Core/Context.hpp"
#include "Sea/Input/EventHandler.hpp"

namespace Sea
{	

	class Window
	{	
	friend class Context;

	public:
		virtual void Run() = 0;
		virtual void Swap() = 0;
		virtual void UseVSync(bool use) = 0;
		virtual void Viewport() = 0;
		virtual void Viewport(u32 h, u32 w) = 0;
		virtual void Viewport(u32 x, u32 y, u32 h, u32 w) = 0;
		void Update();
		void Hide();
		void Show();
		void Close();
		bool IsOpen();
		bool IsClosed();
		void SetSize(f32 w, f32 h);
		void SetResizable(bool resizable);
		void SetTitle(std::string_view title);
		void SetMousePostion(f32 x, f32 y);
		std::pair<f32, f32> GetSize();
		void SetMouseOnMiddlePosistion();
		void GrapMouse();
		void UngrapMouse();
		SDL_Window* GetHandle() { return m_handle; }
		Renderer& GetRenderer() { return *m_renderer; }
		VideoMode& GetVideoMode() { return m_video_mode; }

	protected:
		void SetupFlags();
		void SetupIcon();

	public:
		Window(std::string_view title, VideoMode& proterties);
		Window(const Window&) = default;
		Window(Window &&) = default;
		~Window();

	protected:
		s32 flags;
		bool m_isOpen = false;
		std::string m_title;
		SDL_Window* m_handle;
		VideoMode& m_video_mode;
		Ref<Renderer> m_renderer;
		Ref<Context> m_context;
		
	};

}
