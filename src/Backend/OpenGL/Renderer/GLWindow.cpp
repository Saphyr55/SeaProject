#include "Sea/Backend/OpenGL/Renderer/GLWindow.hpp"
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
			SDL_WINDOW_OPENGL
		);
		if (m_handle == nullptr) throw(std::string("Failed to create window: ") + SDL_GetError());
		m_context = GLContext(SDL_GL_CreateContext(m_handle)); // create context
		gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	}

	GLWindow::GLWindow(WindowProperties& properties) : Window(properties)
	{

	}
}

