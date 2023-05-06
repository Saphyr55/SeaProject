#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "Sea/Renderer/Renderer.hpp"
#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/Context.hpp"
#include "Sea/Core/Input/EventHandler.hpp"

#include <SDL2/SDL.h>

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
		void SetMouseOnMiddlePosistion();
		void GrapMouse();
		void UngrapMouse();
		SDL_Window* GetHandle() { return m_handle; }
		Renderer& GetRenderer() { return *m_renderer; }
		VideoMode& GetVideoMode() { return m_videoMode; }

	protected:
		void SetupFlags();
		void SetupIcon();

	public:
		Window(std::string_view title, VideoMode& proterties);
		Window(const Window&) = default;
		Window(Window&&) = default;

	protected:
		s32 flags;
		bool m_isOpen = false;
		std::string m_title;
		VideoMode m_videoMode;
		Ref<Renderer> m_renderer;
		Ref<Context> m_contextPtr;
		
	};

}
