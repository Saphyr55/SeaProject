#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace Sea
{

    class File;
	class IShader;
	struct Color;

    class Renderer
    {
    public:
        virtual void Enable() const = 0;
        virtual void ClearColor(Color color) const = 0;
        virtual void Clear() const = 0;

    public:
        Renderer();
        ~Renderer();
    };

} 
