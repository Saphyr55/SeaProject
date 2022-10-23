#pragma once

#include <Sea/Renderer/Renderer.hpp>

namespace Sea::Backend::OpenGL
{   
    
    class GLRenderer : public Renderer
    {
    public:
        void ClearColor(Color color) const;
        void Clear() const;

    public:
        GLRenderer();
        ~GLRenderer();
    };
    
} 
