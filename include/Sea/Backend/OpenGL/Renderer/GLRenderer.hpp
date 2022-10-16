#pragma once

#include <Sea/Renderer/Renderer.hpp>

namespace Sea::Backend::OpenGL
{   
    
    class GLRenderer : public Renderer
    {
    public:
        void ClearColor(Color color);
        void Clear();

    public:
        GLRenderer();
        ~GLRenderer();
    };
    
} 
