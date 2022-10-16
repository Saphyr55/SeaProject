#include <Sea/Renderer/Window.hpp>


namespace Sea
{
	Window::Window(std::string title, int width, int height)
	{
	}

	Window::~Window()
	{
	}

	bool Window::IsOpen()
	{
		return m_isOpen;
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


