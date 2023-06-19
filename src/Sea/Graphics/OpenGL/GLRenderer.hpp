#pragma once

#include "Sea/Graphics/Rendering/Renderer.hpp"

namespace Sea
{   
    
    class GLRenderer : public Renderer
    {
    public:
        void Init() override;
        void Enable() const override;
        void ClearColor(Color color) const override;
        void Clear() const override;
	    void DisableBlending() const override;
		void EnableBlending() const override;
        Ref<Shader> ShapeShader() const override;
        Ref<Shader> CreateShader(std::string_view vertexShaderSource, std::string_view fragmentShaderSource) const override;
		Ref<Texture> CreateTexture(std::string_view path, Texture::Type texType, u32 slot) const override;
		Ref<Texture> CreateTexture(File file, Texture::Type texType, u32 slot) const override;
		Ref<Mesh> CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<TextureRef>& textures) const override;
		Ref<Mesh> CreateMesh(std::vector<Vertex>& vertices, std::vector<u32>& indices) const override;

    public:
        GLRenderer();
        ~GLRenderer() = default;

    private:
        Ref<Shader> m_shape_shader;
    };
    
} 
