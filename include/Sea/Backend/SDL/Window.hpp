#pragma once

#include <SDL2/SDL.h>
#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/VideoMode.hpp"
#include "Sea/Renderer/Window.hpp"

namespace Sea::Backend::SDL
{
	class Window : public ::Sea::Window
	{
	public:
		void Run();
		void Swap();
		void UseVSync(bool use);
		void Viewport(u32 x, u32 y, u32 h, u32 w);
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

	public:
		Window(std::string_view title, VideoMode& videoMode);
		Window(const Window&) = default;
		Window(Window&&) = default;
		~Window();

	private:
		s32 m_flags;
		s32 m_renderFlags;
		s32 m_windowId;
		SDL_Window* m_handle;
	};

}