#pragma once

#include <Sea/Renderer/Renderer.hpp>

namespace Sea::Backend::OpenGL
{   
    
    class GLRenderer : public Renderer
    {
    public:
        void ClearColor(Color color) const;
        void Clear() const;
		std::shared_ptr<Shader> CreateShader(File fragFile, File vertFile)const;
        std::shared_ptr<Shader> CreateShader(std::string fragSource, std::string vertSource) const;

    public:
        GLRenderer()=default;
        ~GLRenderer()=default;
    };
    
} 
