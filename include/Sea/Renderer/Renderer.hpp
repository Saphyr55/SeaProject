#pragma once

#include <glm/glm.hpp>

namespace Sea
{
    struct Color;

    class Renderer
    {
    public:
        virtual void ClearColor(Color color) abstract;
        virtual void Clear() abstract;

    public:
        Renderer();
        ~Renderer();
    };
    
} 
