#pragma once

#include <Sea/Graphic/Texture.hpp>
#include <Sea/Graphic/Mesh.hpp>

namespace Sea 
{

	class Shader;
	class Window;
	struct VideoMode;

	class Factory
	{
	public:
		static Ref<Shader> CreateShader(std::string_view vertexShaderSource, std::string_view fragmentShaderSource);
		static Ref<Texture> CreateTexture(std::string_view path, Texture::Type texType, u32 slot);
		static Ref<Texture> CreateTexture(File file, Texture::Type texType, u32 slot);
		static Ref<Window> CreateWindow(std::string_view title, VideoMode& proterties);
		static Ref<Mesh> CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<RTexture>& textures);
		static Ref<Mesh> CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices);
	};

}