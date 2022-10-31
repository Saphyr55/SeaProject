#include "Sea/Backend/OpenGL/Renderer/GLWindow.hpp"
#include "Sea/Backend/OpenGL/Renderer/GLRenderer.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Backend/OpenGL/GLContext.hpp"


namespace Sea::Backend::OpenGL
{
	void GLWindow::Run()
	{
		OpenGL::Init();
		SetupIcon();
		SetupFlags();

		flags |= SDL_WINDOW_OPENGL;

		m_handle = SDL_CreateWindow(
			m_properties.Title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_properties.Width, m_properties.Height, flags
		);

		if (m_handle == nullptr) throw(std::string("Failed to create window: ") + SDL_GetError());
		
		m_contextPtr= std::make_shared<GLContext>(*this);

		gladLoadGLLoader(SDL_GL_GetProcAddress); // Check OpenGL properties

		if (GL_VERSION == NULL) throw("Enable to init OpenGL");
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
		Viewport(m_properties.Width, m_properties.Height);
	}

	void GLWindow::Viewport(u32 h, u32 w)
	{
		Viewport(0, 0, m_properties.Width, m_properties.Height);
	}

	void GLWindow::Viewport(u32 x, u32 y, u32 h, u32 w)
	{
		glViewport(x, y, h, w);
	}

	GLWindow::GLWindow(Window::Properties& properties) :
		Window(properties)
	{
		m_renderer = std::make_shared<GLRenderer>();
	}


}

