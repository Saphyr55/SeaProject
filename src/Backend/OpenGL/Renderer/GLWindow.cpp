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
			m_properties.title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_properties.width, m_properties.height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
		);

		if (m_handle == nullptr) throw(std::string("Failed to create window: ") + SDL_GetError());
		
		m_contextPtr= std::make_shared<GLContext>(*this);

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

	void GLWindow::UseVSync(bool use)
	{
		SDL_GL_SetSwapInterval(use);
	}

	GLWindow::GLWindow(Window::Properties& properties) :
		Window(properties)
	{
		m_renderer = std::make_shared<GLRenderer>(GLRenderer());
	}
}

