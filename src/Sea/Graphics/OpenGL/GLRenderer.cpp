#include "Sea/Graphics/OpenGL/GLRenderer.hpp"
#include "Sea/Graphics/OpenGL/GL.hpp"
#include "Sea/Graphics/OpenGL/GLShader.hpp"
#include "Sea/Graphics/OpenGL/GLMesh.hpp"
#include "Sea/Graphics/OpenGL/GLTexture.hpp"
#include "Sea/Core/File.hpp"
#include "Sea/Core/Color.hpp"
#include "Sea/Graphics/OpenGL/GLWindow.hpp"

namespace Sea
{
	void GLRenderer::Init()
	{
		if (!m_shape_shader)
			m_shape_shader = CreateShader(
				"src/Sea/Resources/Shaders/Shape.vert",
				"src/Sea/Resources/Shaders/Shape.frag"
			);
	}

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

	Ref<Shader> GLRenderer::ShapeShader() const
	{
		return m_shape_shader;
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

	Ref<Mesh> GLRenderer::CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<TextureRef>& textures) const
	{
		return std::make_shared<GLMesh>(vertices, indices, textures);
	}

	Ref<Mesh> GLRenderer::CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices) const
	{
		return std::make_shared<GLMesh>(vertices, indices);
	}

	GLRenderer::GLRenderer()
	{
		OpenGL::Init();
	}

}


