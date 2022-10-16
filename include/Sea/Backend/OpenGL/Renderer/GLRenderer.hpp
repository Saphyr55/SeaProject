#pragma once

#include <Sea/Renderer/Renderer.hpp>

namespace Sea::Backend::OpenGL
{
    class GLRenderer : public Renderer
    {
    public:
        void ClearColor(glm::vec4 color);
        void ClearColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
        void Clear();

    public:
        GLRenderer();
        ~GLRenderer();
    };
    
} 
