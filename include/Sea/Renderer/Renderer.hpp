#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace Sea
{

    struct Color;
    class File;
    class Shader;

    class Renderer
    {
    public:
        virtual void ClearColor(Color color) const = 0;
        virtual void Clear() const = 0;
        virtual std::shared_ptr<Shader> CreateShader(File fragFile, File vertFile)const=0;
		virtual std::shared_ptr<Shader> CreateShader(std::string fragSource, std::string vertSource)const = 0;

    public:
        Renderer();
        ~Renderer();
    };

} 
