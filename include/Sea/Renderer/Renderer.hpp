#pragma once

#include <glm/glm.hpp>

namespace Sea
{
    class Renderer
    {
    public:
        virtual void ClearColor(glm::vec4 color) abstract;
        virtual void ClearColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) abstract;
        virtual void Clear() abstract;

    public:
        Renderer();
        ~Renderer();
    };
    
} 
