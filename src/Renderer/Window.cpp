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
	Ref<Window> Window::Of(Window::Properties &properties)
	{	
		switch (properties.Context)
		{
		case ContextType::OpenGL: 
			return CreateRef<Backend::OpenGL::GLWindow>(properties);
		default: 
			return CreateRef<Backend::OpenGL::GLWindow>(properties);
		}
	}

	Window::Window(Window::Properties &proterties) 
		: m_properties(proterties), m_handle(nullptr)
	{
		Molder::context = m_properties.Context;
		Log::Info() << 
			"Window create with {" << 
			"width=" << m_properties.Width << 
			", height=" <<m_properties.Height << 
			", title="  <<m_properties.Title << "}";
		Log::Info() << "Setup context with " << Context::contextType_tostring(m_properties.Context);
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
		m_properties.Width = w;
		m_properties.Height = h;
		SDL_SetWindowSize(m_handle, m_properties.Width, m_properties.Height);
	}

	void Window::SetResizable(bool resizable)
	{
		m_properties.Resizable = resizable;
		SDL_SetWindowResizable(m_handle, (SDL_bool) m_properties.Resizable);
	}

	void Window::SetTitle(std::string title)
	{
		m_properties.Title = title;
		SDL_SetWindowTitle(m_handle, title.c_str());
	}

	void Window::SetMousePostion(f32 x, f32 y)
	{
		SDL_WarpMouseInWindow(nullptr, x, y);
	}

	void Window::SetMouseOnMiddlePosistion()
	{
		SetMousePostion(m_properties.Width / 2, m_properties.Height / 2);
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
		if (m_properties.Resizable) flags |= SDL_WINDOW_RESIZABLE;
		if (m_properties.Fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
		if (m_properties.Maximazed) flags |= SDL_WINDOW_MAXIMIZED;
	}

	void Window::CreateEvent()
	{	
		m_event = std::make_shared<Event>();
	}

	void Window::Update()
	{	
		SDL_GetWindowSize(m_handle, (s32*)&m_properties.Width, (s32*)&m_properties.Height);
	}

	void Window::SetupIcon()
	{				
		if (!m_properties.FileIcon.empty())
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
	}

}
