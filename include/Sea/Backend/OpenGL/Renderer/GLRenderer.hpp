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
		std::shared_ptr<Shader> CreateShader(File fragFile, File vertFile)const;
        std::shared_ptr<Shader> CreateShader(std::string fragSource, std::string vertSource) const;
        std::shared_ptr<Mesh> CreateMesh() const;

    public:
        GLRenderer()=default;
        ~GLRenderer()=default;
    };
    
} 
