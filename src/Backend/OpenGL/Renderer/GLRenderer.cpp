#include <Sea/Backend/OpenGL/Renderer/GLRenderer.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Common/Color.hpp>
#include <mcl/Logger.hpp>

namespace Sea::Backend
{
	void OpenGL::GLRenderer::ClearColor(Color color) const
	{	
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGL::GLRenderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	OpenGL::GLRenderer::GLRenderer()
	{

	}

	OpenGL::GLRenderer::~GLRenderer()
	{

	}
}


