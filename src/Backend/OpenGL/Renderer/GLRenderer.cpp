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
		glEnable(GL_DEPTH_CLAMP);
	}

	void GLRenderer::ClearColor(Color color) const
	{	
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRenderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	std::shared_ptr<Shader> GLRenderer::CreateShader(File fragFile, File vertFile) const
	{
		return std::make_shared<GLShader>(fragFile, vertFile);
	}
	
	std::shared_ptr<Shader> GLRenderer::CreateShader(std::string fragSource, std::string vertSource) const
	{
		return std::make_shared<GLShader>(fragSource, vertSource);
	}

	std::shared_ptr<Mesh> GLRenderer::CreateMesh() const
	{
		return std::make_shared<GLMesh>();
	}

}


