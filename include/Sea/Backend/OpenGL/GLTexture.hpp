#pragma once

#include <Sea/Common/CommonType.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Graphic/Shader.hpp>
#include <Sea/Common/File.hpp>

namespace Sea::Backend::OpenGL
{

    class GLTexture
    {
    public:
        
        void TexUniform(ShaderPtr shader, const char* uniform, u32 uni);
        void Bind();
        void Unbind();
        void Delete();
        u32 GetId();
        s32 GetWidth();
        s32 GetHeight();

		GLTexture(File image, u32 texType, u32 slot, u32 format, u32 pixelType);
		~GLTexture() = default;

    private:
        void SetDefaultParameteri();

    private:
        u32 id, m_type, m_slot, m_format, m_pixelType;
        s32 width, height;
        File imageFile;
    };
    
    using GLTexturePtr = std::shared_ptr<GLTexture>;

}
