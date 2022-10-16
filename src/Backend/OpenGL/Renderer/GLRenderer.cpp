#include <Sea/Backend/OpenGL/Renderer/GLRenderer.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Common/Color.hpp>

namespace Sea::Backend
{
	void OpenGL::GLRenderer::ClearColor(Color color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
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


