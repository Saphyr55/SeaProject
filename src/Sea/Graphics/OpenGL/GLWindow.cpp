#include "Sea/Graphics/OpenGL/GLWindow.hpp"
#include "Sea/Graphics/OpenGL/GLRenderer.hpp"
#include "Sea/Graphics/OpenGL/GL.hpp"
#include "Sea/Graphics/OpenGL/GLContext.hpp"
#include <fmt/core.h>

namespace Sea
{
	void GLWindow::Init()
	{	
		SetupFlags();
		
		m_flags |= SDL_WINDOW_OPENGL;

		m_handle = SDL_CreateWindow
		(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_video_mode.Width,
			m_video_mode.Height,
			m_flags
		);

		if (!m_handle) 
		{
			auto msg = fmt::format("Failed to create window {}", SDL_GetError());
			throw std::exception(msg.c_str());
		}

		m_context = MakeRef<GLContext>(*this);

		if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0 && GL_VERSION == NULL)
		{
			throw std::exception("Enable to init OpenGL");
		}
	}

	void GLWindow::Swap()
	{
		SDL_GL_SwapWindow(m_handle);
	}

	void GLWindow::UseVSync(bool use)
	{
		SDL_GL_SetSwapInterval(use);
	}

	void GLWindow::Viewport()
	{
		Viewport(m_video_mode.Width, m_video_mode.Height);
	}

	void GLWindow::Viewport(u32 h, u32 w)
	{
		Viewport(0, 0, m_video_mode.Width, m_video_mode.Height);
	}

	void GLWindow::Viewport(u32 x, u32 y, u32 h, u32 w)
	{
		glViewport(x, y, h, w);
	}

	GLWindow::GLWindow(std::string_view title, VideoMode& videoMode) : Window(title, videoMode)
	{
		Init();
		m_renderer = std::make_shared<GLRenderer>();
		m_renderer->Init();
		m_renderer->Enable();
		RenderService::Set(m_renderer);
	}


}

