#include "Sea/Backend/OpenGL/GLContext.hpp"

namespace Sea::Backend::OpenGL
{

	GLContext::GLContext(::Sea::Backend::SDL::Window& window)
		: m_handle(SDL_GL_CreateContext(window.GetHandle()))
	{
		if (m_handle == nullptr) throw("Failed to create OpenGL context");
	}

	GLContext::~GLContext()
	{
		SDL_GL_DeleteContext(m_handle);
	}
}