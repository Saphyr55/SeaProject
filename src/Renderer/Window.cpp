#include "Sea/Renderer/Window.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Common/File.hpp"
#include <SDL2/SDL_image.h>
#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea
{

	Window::Window(std::string_view title, VideoMode& videoMode)
		: m_videoMode(videoMode), m_title(title)
	{
		Log::Info() << 
			"Window create with {" << 
			"width=" << m_videoMode.Width <<
			", height=" << m_videoMode.Height <<
			", title="  << m_title << "}";
	}

	void Window::Viewport()
	{
		Viewport(m_videoMode.Width, m_videoMode.Height);
	}

	void Window::Viewport(u32 h, u32 w)
	{
		Viewport(0, 0, m_videoMode.Width, m_videoMode.Height);
	}
	
	void Window::Viewport(u32 x, u32 y, u32 h, u32 w) 
	{
		m_renderer->Viewport(x, y, h, w);
	}

	
}
