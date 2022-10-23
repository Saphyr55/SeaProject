#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace Sea
{

    struct Color;

    class Renderer
    {
    public:
        virtual void ClearColor(Color color) const = 0;
        virtual void Clear() const = 0;

    public:
        Renderer();
        ~Renderer();
    };

} 
