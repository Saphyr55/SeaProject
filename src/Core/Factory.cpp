#include <Sea/Core/Factory.hpp>
#include <Sea/Core/Mold.hpp>
#include <Sea/Backend/OpenGL/Renderer/GLWindow.hpp>
#include <Sea/Backend/OpenGL/GLShader.hpp>
#include <Sea/Backend/OpenGL/GLShader.hpp>
#include <Sea/Backend/OpenGL/GLTexture.hpp>
#include <Sea/Backend/OpenGL/GLMesh.hpp>

#include <memory>

namespace Sea
{
	Ref<Shader> Factory::CreateShader(std::string_view vertexShaderSource, std::string_view fragmentShaderSource)
	{
		switch (Molder::API)
		{
		case GraphicsAPI::OpenGL:
			return std::make_shared<Backend::OpenGL::GLShader>(vertexShaderSource, fragmentShaderSource);
			break;
		default:
			return std::make_shared<Backend::OpenGL::GLShader>(vertexShaderSource, fragmentShaderSource);
			break;
		}
	}
	
	Ref<Texture> Factory::CreateTexture(std::string_view path, Texture::Type texType, u32 slot)
	{
		switch (Molder::API)
		{
		case GraphicsAPI::OpenGL:
			return std::make_shared<Backend::OpenGL::GLTexture>(path, texType, slot);
			break;
		default:			
			return std::make_shared<Backend::OpenGL::GLTexture>(path, texType, slot);
			break;
		}
	}
	
	Ref<Texture> Factory::CreateTexture(File file, Texture::Type texType, u32 slot)
	{
		switch (Molder::API)
		{
		case GraphicsAPI::OpenGL:
			return std::make_shared<Backend::OpenGL::GLTexture>(file, texType, slot);
			break;
		default:
			return std::make_shared<Backend::OpenGL::GLTexture>(file, texType, slot);
			break;
		}
	}


	Ref<Window> Factory::CreateWindow(std::string_view title, VideoMode& proterties)
	{
		switch (Molder::API)
		{
		case GraphicsAPI::OpenGL:
			return std::make_shared<Backend::OpenGL::GLWindow>(title, proterties);
			break;
		default:
			return std::make_shared<Backend::OpenGL::GLWindow>(title, proterties);
			break;
		}
	}
	
	Ref<Mesh> Factory::CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<RTexture>& textures)
	{
		switch (Molder::API)
		{
		case GraphicsAPI::OpenGL:
			return std::make_shared<Backend::OpenGL::GLMesh>(vertices, indices, textures);
			break;
		default:
			return std::make_shared<Backend::OpenGL::GLMesh>(vertices, indices, textures);
			break;
		}
	}

	Ref<Mesh> Factory::CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices)
	{
		switch (Molder::API)
		{
		case GraphicsAPI::OpenGL:
			return std::make_shared<Backend::OpenGL::GLMesh>(vertices, indices);
			break;
		default:
			return std::make_shared<Backend::OpenGL::GLMesh>(vertices, indices);
			break;
		}
	}

}
