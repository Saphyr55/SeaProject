#include "Sea/Graphic/OpenGL/Renderer/GLWindow.hpp"
#include "Sea/Graphic/OpenGL/Renderer/GLRenderer.hpp"
#include "Sea/Graphic/OpenGL/GL.hpp"
#include "Sea/Graphic/OpenGL/GLContext.hpp"

namespace Sea::Backend::OpenGL
{
	void GLWindow::Init()
	{	
		SetupIcon();
		SetupFlags();
		
		flags |= SDL_WINDOW_OPENGL;

		m_handle = SDL_CreateWindow
		(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_videoMode.Width,
			m_videoMode.Height,
			flags
		);

		if (!m_handle) throw std::exception(std::string("Failed to create window" + std::string(SDL_GetError())).c_str());

		m_contextPtr = MakeRef<GLContext>(*this); // Create gl context

		gladLoadGLLoader(SDL_GL_GetProcAddress); // Check OpenGL properties

		if (GL_VERSION == NULL) throw std::exception("Enable to init OpenGL");
	}

	void GLWindow::Run()
	{
		m_isOpen = true;
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
		Viewport(m_videoMode.Width, m_videoMode.Height);
	}

	void GLWindow::Viewport(u32 h, u32 w)
	{
		Viewport(0, 0, m_videoMode.Width, m_videoMode.Height);
	}

	void GLWindow::Viewport(u32 x, u32 y, u32 h, u32 w)
	{
		glViewport(x, y, h, w);
	}

	GLWindow::GLWindow(std::string_view title, VideoMode& videoMode) : Window(title, videoMode)
	{
		m_renderer = MakeRef<GLRenderer>();
		Init();
		m_renderer->Enable();
		RenderService::Set(m_renderer);
	}


}

