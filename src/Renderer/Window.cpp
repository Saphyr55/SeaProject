#include "Sea/Renderer/Window.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"

namespace Sea
{
	Window::Window(std::string title, u32 width, u32 height)
		: m_title(title), m_width(width), m_height(height), m_handle(nullptr)
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
