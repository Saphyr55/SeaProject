#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "Sea/Core/Clock.hpp"
#include "Sea/Core/Common.hpp"
#include "Sea/Core/Context.hpp"
#include "Sea/Core/Application.hpp"
#include "Sea/Core/Handler.hpp"
#include "Sea/Graphics/Rendering/Renderer.hpp"
#include "Sea/Input/EventHandler.hpp"

namespace Sea
{	

	class Window : public Handler<Application&>
	{	
	using WindowHandlerRef = std::shared_ptr<Handler<Window&>>;
	friend class Context;

	public:
		virtual void Swap() = 0;
		virtual void UseVSync(bool use) = 0;
		virtual void Viewport() = 0;
		virtual void Viewport(u32 h, u32 w) = 0;
		virtual void Viewport(u32 x, u32 y, u32 h, u32 w) = 0;
	
	public:
		void Handle(Sea::Application& app);
		void Attach(std::shared_ptr<Handler<Window&>> clock);
		void Update();
		void Hide();
		void Show();
		void Close();
		bool IsClosed();
		void SetSize(f32 w, f32 h);
		void SetResizable(bool resizable);
		void SetTitle(std::string_view title);
		void SetMousePostion(f32 x, f32 y);
		std::pair<f32, f32> GetSize();
		void SetMouseOnMiddlePosistion();
		void GrapMouse();
		void UngrapMouse();
		bool IsOpen() { return m_is_open; }
		Renderer& GetRenderer() { return *m_renderer; }
		Clock& GetClock() { return m_clock; }
		FrameRate& GetFrameRate() { return m_frame_rate; }
		SDL_Window* GetHandle() { return m_handle; }

	protected:
		void SetupFlags();

	public:
		Window(std::string_view title, VideoMode& proterties);
		Window(const Window&) = default;
		Window(Window &&) = default;
		~Window();

	protected:
		std::vector<WindowHandlerRef> m_handlers;
		Ref<Renderer> m_renderer;
		Ref<Context> m_context;
		SDL_Window* m_handle;
		Clock m_clock;
		FrameRate m_frame_rate;
		VideoMode& m_video_mode;
		std::string m_title;
		s32 m_flags;
		bool m_is_open;
	};

}
