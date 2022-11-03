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
		EnableBlending();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW); 
	}

	void GLRenderer::ClearColor(Color color) const
	{	
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRenderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderer::DisableBlending() const
	{
		glDisable(GL_BLEND);
	}

	void GLRenderer::EnableBlending() const
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

}


