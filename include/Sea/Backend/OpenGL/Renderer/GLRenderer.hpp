#pragma once

#include <Sea/Renderer/Renderer.hpp>

namespace Sea::Backend::OpenGL
{   
    
    class GLRenderer : public Renderer
    {
    public:
        void Enable() const;
        void ClearColor(Color color) const;
        void Clear() const;
	    void DisableBlending() const;
		void EnableBlending() const;
		Ref<Shader> CreateShader(std::string_view vertexShaderSource, std::string_view fragmentShaderSource) const;
		Ref<Texture> CreateTexture(std::string_view path, Texture::Type texType, u32 slot) const;
		Ref<Texture> CreateTexture(File file, Texture::Type texType, u32 slot) const;
		Ref<Mesh> CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<RTexture>& textures) const;
		Ref<Mesh> CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices) const;

    public:
        GLRenderer()=default;
        ~GLRenderer()=default;
    };
    
} 
