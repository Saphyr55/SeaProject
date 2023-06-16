#include <SDL2/SDL_image.h>

#include "Sea/Graphics/Rendering/Window.hpp"
#include "Sea/Graphics/OpenGL/Renderer/GLWindow.hpp"
#include "Sea/Graphics/OpenGL/GL.hpp"
#include "Sea/Core/File.hpp"

namespace Sea
{

	Window::Window(std::string_view title, VideoMode& videoMode)
		: m_video_mode(videoMode), m_handle(nullptr), m_title(title)
	{
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_handle);
	}

	bool Window::IsOpen()
	{
		return m_isOpen;
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
		m_isOpen = false;
	}

	bool Window::IsClosed()
	{
		return !m_isOpen;
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
		flags = SDL_WINDOW_SHOWN;
		if (m_video_mode.Resizable) flags |= SDL_WINDOW_RESIZABLE;
		if (m_video_mode.Fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
		if (m_video_mode.Maximazed) flags |= SDL_WINDOW_MAXIMIZED;
	}

	void Window::Update()
	{	
		SDL_GetWindowSize(m_handle, (s32*)&m_video_mode.Width, (s32*)&m_video_mode.Height);
	}

	/**
	 * Deprecated
	 */
	void Window::SetupIcon()
	{	
		/*
		if (!m_videoMode.FileIcon.empty())
		{
			auto file = File(m_properties.FileIcon);
			if (file.Exist())
			{
				SDL_Surface* icon = IMG_Load(file.GetPath().c_str());
				if (!icon)
				{
					Log::Warning() << "Icon was not loading : " << file.GetPath();
					return;
				}
				Log::Info() << "Image Load : " << file.GetPath();
				SDL_SetWindowIcon(m_handle, icon);
				SDL_FreeSurface(icon);
			}
			else Log::Warning() << file.GetPath() << " not exist impossible to setup an icon";
		}
		*/
	}

}
