#include <Sea/Backend/OpenGL/Renderer/GLRenderer.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Common/Color.hpp>
#include <iostream>

namespace Sea::Backend
{
	void OpenGL::GLRenderer::ClearColor(Color color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGL::GLRenderer::Clear()
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


