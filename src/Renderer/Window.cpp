#include "Sea/Renderer/Window.hpp"
#include "Sea/Backend/OpenGL/Renderer/GLWindow.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"

namespace Sea
{
	std::shared_ptr<Window> Window::Of(Window::Properties &properties)
	{
		switch (properties.Context)
		{
		case ContextType::OpenGL: 
			return std::make_shared<Backend::OpenGL::GLWindow>(properties);
		default: 
			return std::make_shared<Backend::OpenGL::GLWindow>(properties);
		}
	}

	Window::Window(Window::Properties &proterties) 
		: m_properties(proterties), m_handle(nullptr)
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

	void Window::CreateEvent()
	{	
		m_event = std::make_shared<Event>();
	}

	void Window::Update()
	{	
		SDL_GetWindowSize(m_handle, (s32*)&m_properties.Width, (s32*)&m_properties.Height);
	}

}
