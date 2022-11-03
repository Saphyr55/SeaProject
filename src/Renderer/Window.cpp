#include "Sea/Renderer/Window.hpp"
#include "Sea/Backend/OpenGL/Renderer/GLWindow.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Core/Mold.hpp"
#include "Sea/Common/File.hpp"
#include <SDL2/SDL_image.h>
#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea
{

	Window::Window(std::string_view title, VideoMode& videoMode)
		: m_videoMode(videoMode), m_handle(nullptr), m_title(title), m_event(CreateRef<EventHandler>(*this))
	{
		Log::Info() << 
			"Window create with {" << 
			"width=" << m_videoMode.Width <<
			", height=" << m_videoMode.Height <<
			", title="  << m_title << "}";
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
		m_videoMode.Width = w;
		m_videoMode.Height = h;
		SDL_SetWindowSize(m_handle, m_videoMode.Width, m_videoMode.Height);
	}

	void Window::SetResizable(bool resizable)
	{
		m_videoMode.Resizable = resizable;
		SDL_SetWindowResizable(m_handle, (SDL_bool)m_videoMode.Resizable);
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

	void Window::SetMouseOnMiddlePosistion()
	{
		SetMousePostion(m_videoMode.Width / 2, m_videoMode.Height / 2);
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
		if (m_videoMode.Resizable) flags |= SDL_WINDOW_RESIZABLE;
		if (m_videoMode.Fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
		if (m_videoMode.Maximazed) flags |= SDL_WINDOW_MAXIMIZED;
	}

	void Window::Update()
	{	
		SDL_GetWindowSize(m_handle, (s32*)&m_videoMode.Width, (s32*)&m_videoMode.Height);
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
