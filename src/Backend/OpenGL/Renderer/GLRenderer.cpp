#include <mcl/Logger.hpp>

#include <Sea/Backend/OpenGL/Renderer/GLRenderer.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Backend/OpenGL/GLShader.hpp>
#include <Sea/Backend/OpenGL/GLMesh.hpp>
#include <Sea/Common/File.hpp>
#include <Sea/Common/Color.hpp>

namespace Sea::Backend::OpenGL
{

	void GLRenderer::Enable() const
	{
		glEnable(GL_DEPTH_TEST);
		// glEnable(GL_DEPTH_CLAMP);
		glDepthFunc(GL_LESS);
	}

	void GLRenderer::ClearColor(Color color) const
	{	
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRenderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}


