#include <mcl/Logger.hpp>

#include <Sea/Backend/OpenGL/Renderer/GLRenderer.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Backend/OpenGL/GLShader.hpp>
#include <Sea/Backend/OpenGL/GLMesh.hpp>
#include <Sea/Backend/OpenGL/GLTexture.hpp>
#include <Sea/Common/File.hpp>
#include <Sea/Common/Color.hpp>
#include <Sea/Backend/OpenGL/Renderer/GLWindow.hpp>

namespace Sea::Backend::OpenGL
{

	void GLRenderer::Enable() const
	{
		glEnable(GL_DEPTH_TEST);
		// glEnable(GL_CULL_FACE);
		// glCullFace(GL_FRONT);
		// glFrontFace(GL_CCW); 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	}

	Ref<Shader> GLRenderer::CreateShader(std::string_view vertexShaderSource, std::string_view fragmentShaderSource) const
	{
		return std::make_shared<GLShader>(vertexShaderSource, fragmentShaderSource);
	}

	Ref<Texture> GLRenderer::CreateTexture(std::string_view path, Texture::Type texType, u32 slot) const
	{
		return std::make_shared<GLTexture>(path, texType, slot);
	}

	Ref<Texture> GLRenderer::CreateTexture(File file, Texture::Type texType, u32 slot) const
	{
		return std::make_shared<GLTexture>(file, texType, slot);
	}

	Ref<Mesh> GLRenderer::CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<RTexture>& textures) const
	{
		return std::make_shared<Backend::OpenGL::GLMesh>(vertices, indices, textures);
	}

	Ref<Mesh> GLRenderer::CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices) const
	{
		return std::make_shared<Backend::OpenGL::GLMesh>(vertices, indices);
	}

}


