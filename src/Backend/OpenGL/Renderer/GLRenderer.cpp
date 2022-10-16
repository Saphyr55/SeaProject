#include <Sea/Backend/OpenGL/Renderer/GLRenderer.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>

namespace Sea::Backend
{
	void OpenGL::GLRenderer::ClearColor(glm::vec4 color)
	{
		ClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGL::GLRenderer::ClearColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGL::GLRenderer::Clear()
	{

	}

	OpenGL::GLRenderer::GLRenderer()
	{

	}

	OpenGL::GLRenderer::~GLRenderer()
	{

	}
}


