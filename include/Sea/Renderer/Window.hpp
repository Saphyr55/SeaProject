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
		virtual void Update() = 0;
		virtual void Hide() = 0;
		virtual void Show() = 0;
		virtual void Close() = 0;
		virtual bool IsOpen() = 0;
		virtual bool IsClosed() = 0;
		virtual void SetSize(f32 w, f32 h) = 0;
		virtual void SetResizable(bool resizable) = 0;
		virtual void SetTitle(std::string_view title) = 0;
		virtual void SetMousePostion(f32 x, f32 y) = 0;
		virtual void SetMouseOnMiddlePosistion() = 0;
		virtual void GrapMouse() = 0;
		virtual void UngrapMouse() = 0;
		void Viewport(u32 x, u32 y, u32 h, u32 w);
		void Viewport();
		void Viewport(u32 h, u32 w);
		Renderer& GetRenderer() { return *m_renderer; }
		VideoMode& GetVideoMode() { return m_videoMode; }

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
