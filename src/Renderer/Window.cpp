#include "Sea/Renderer/Window.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"

namespace Sea
{
	Window::Window(std::string title, std::uint32_t width, std::uint32_t height)
		: m_title(title), m_width(width), m_height(height), m_handle(nullptr)
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
	}

	void Window::Show()
	{
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
