#include "Sea/Renderer/Window.hpp"
#include "Sea/Backend/OpenGL/Renderer/GLWindow.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"

namespace Sea
{
	std::shared_ptr<Window> Window::Of(WindowProperties& properties)
	{	
		switch (properties.context)
		{
		case ContextType::OpenGL:
			return std::make_shared<Backend::OpenGL::GLWindow>(properties);
		} 
		return std::make_shared<Backend::OpenGL::GLWindow>(properties);
	}

	Window::Window(WindowProperties& proterties)
		: m_title(proterties.title), m_width(proterties.width), m_height(proterties.height), m_handle(nullptr)
	{ }

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
}
