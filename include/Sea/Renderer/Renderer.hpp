#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Sea/Graphic/Texture.hpp>

namespace Sea
{

    class File;

    struct Color;
	struct VideoMode;
	struct Vertex;

	class Shader;
    class Window;
    class Mesh;

    class Renderer
    {
    public:
		virtual Ref<Shader> CreateShader(std::string_view vertexShaderSource, std::string_view fragmentShaderSource) const = 0;
		virtual Ref<Texture> CreateTexture(std::string_view path, Texture::Type texType, u32 slot) const = 0;
		virtual Ref<Texture> CreateTexture(File file, Texture::Type texType, u32 slot) const = 0;
		virtual Ref<Mesh> CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<Ref<Texture>>& textures) const = 0;
		virtual Ref<Mesh> CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices) const = 0;
        virtual void DisableBlending() const = 0;
        virtual void EnableBlending() const = 0;
        virtual void Enable() const = 0;
        virtual void ClearColor(Color color) const = 0;
        virtual void Clear() const = 0;

    public:
        Renderer();
        ~Renderer();
    };

	class RenderService
	{
	private:
        static Ref<Renderer> m_renderer;

	public:
        static void Set(Ref<Renderer> renderer) { m_renderer = renderer; }
        static Renderer& Get() { return *m_renderer; }
    };

} 
