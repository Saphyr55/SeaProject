#include <SDL2/SDL_image.h>
#include <cassert>

#include "Sea/Graphics/Rendering/Window.hpp"
#include "Sea/Core/File.hpp"
#include "Sea/Core/Clock.hpp"

namespace Sea
{

	Window::Window(std::string_view title, VideoMode& videoMode) : 
		m_video_mode(videoMode),
		m_handle(nullptr),
		m_title(title),
		m_is_open(false),
		m_flags(SDL_WINDOW_HIDDEN) { }
	
	Window::~Window()
	{
		SDL_DestroyWindow(m_handle);
	}

	void Window::Hide()
	{
		SDL_HideWindow(m_handle);
	}

	void Window::Show()
	{
		SDL_ShowWindow(m_handle);
	}

	void Window::Close()
	{
		m_is_open = false;
	}

	bool Window::IsClosed()
	{
		return !m_is_open;
	}

	void Window::SetSize(f32 w, f32 h)
	{
		m_video_mode.Width = w;
		m_video_mode.Height = h;
		SDL_SetWindowSize(m_handle, m_video_mode.Width, m_video_mode.Height);
	}

	void Window::SetResizable(bool resizable)
	{
		m_video_mode.Resizable = resizable;
		SDL_SetWindowResizable(m_handle, (SDL_bool)m_video_mode.Resizable);
	}

	void Window::SetTitle(std::string_view title)
	{	
		m_title = title;
		SDL_SetWindowTitle(m_handle, title.data());
	}

	void Window::SetMousePostion(f32 x, f32 y)
	{
		SDL_WarpMouseInWindow(nullptr, x, y);
	}

	std::pair<f32, f32> Window::GetSize()
	{
		auto w = new int;
		auto h = new int;
		SDL_GetWindowSize(m_handle, w, h);
		return std::make_pair(*w, *h);
	}

	void Window::SetMouseOnMiddlePosistion()
	{
		SetMousePostion(m_video_mode.Width / 2, m_video_mode.Height / 2);
	}

	void Window::GrapMouse()
	{
		SDL_SetWindowMouseGrab(m_handle, SDL_TRUE);
	}

	void Window::UngrapMouse()
	{
		SDL_SetWindowMouseGrab(m_handle, SDL_FALSE);
	}

	void Window::SetupFlags()
	{	
		if (m_video_mode.Resizable) m_flags |= SDL_WINDOW_RESIZABLE;
		if (m_video_mode.Fullscreen) m_flags |= SDL_WINDOW_FULLSCREEN;
		if (m_video_mode.Maximazed) m_flags |= SDL_WINDOW_MAXIMIZED;
	}

	void Window::Handle(Sea::Application& app)
	{		
		assert(m_handle != nullptr);
		m_is_open = true;
		Show();
		while (IsOpen())
		{
			Update();
			for (auto handler : m_handlers)
			{	
				m_clock.Start(m_frame_rate);
				handler->Handle(*this);
				Swap();
				m_clock.End(m_frame_rate);
			}
		}
	}

	void Window::Attach(std::shared_ptr<Handler<Window&>> handler)
	{
		m_handlers.push_back(handler);
	}

	void Window::Update()
	{
		SDL_GetWindowSize(m_handle, (s32*)&m_video_mode.Width, (s32*)&m_video_mode.Height);
	}

}
