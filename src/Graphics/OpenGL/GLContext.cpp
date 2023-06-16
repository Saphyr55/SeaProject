#include "Sea/Graphics/OpenGL/GLContext.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea::Backend::OpenGL
{
	GLContext::GLContext(Window& window) : m_handle(SDL_GL_CreateContext(window.GetHandle()))
	{
		if (m_handle == nullptr) throw("Failed to create OpenGL context");
	}

	GLContext::~GLContext()
	{
		SDL_GL_DeleteContext(m_handle);
	}
}