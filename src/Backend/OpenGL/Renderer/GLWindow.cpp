#include "Sea/Backend/OpenGL/Renderer/GLWindow.hpp"
#include "Sea/Backend/OpenGL/Renderer/GLRenderer.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Backend/OpenGL/GLContext.hpp"


namespace Sea::Backend::OpenGL
{
	void GLWindow::Run()
	{
		OpenGL::Init();

		m_handle = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_width, m_height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
		);

		if (m_handle == nullptr) throw(std::string("Failed to create window: ") + SDL_GetError());
		 
		gl_context = SDL_GL_CreateContext(m_handle);

		gladLoadGLLoader(SDL_GL_GetProcAddress); // Check OpenGL properties

		if (GL_VERSION == NULL) throw("Enable to init OpenGL");

		// Disable depth test and face culling.
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}

	void GLWindow::Swap()
	{
		SDL_GL_SwapWindow(m_handle);
	}

	void GLWindow::CreateContext()
	{	
		gl_context = SDL_GL_CreateContext(m_handle);

	}

	GLWindow::GLWindow(WindowProperties& properties) : 
		Window(properties)
	{
		m_renderer = std::make_shared<GLRenderer>(GLRenderer());
	}
}

