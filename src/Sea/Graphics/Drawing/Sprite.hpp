#pragma once

#include "Sea/Graphics/Drawing/Drawable.hpp"

namespace Sea
{

    class Sprite : public Drawable
    {  

    public:
        virtual void Draw() = 0;
        
    public:
        Sprite() = default;
        virtual ~Sprite() = default;

    protected:
        Ref<Mesh> m_mesh;
    };

    
}