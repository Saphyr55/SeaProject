#pragma once

#include "Sea/Graphics/Rendering/Renderer.hpp"

namespace Sea
{
    class Drawable
    {
    protected:
        const Renderer& renderer = RenderService::Get();

    public:
        virtual void Draw() = 0;

    public:
        Drawable() = default;
        virtual ~Drawable() = default;
    };

}
