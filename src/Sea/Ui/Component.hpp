#pragma once

#include <functional>

#include "Sea/Core/Common.hpp"
#include "Sea/Graphics/Drawing/Shape.hpp"
#include "Sea/Ui/Anchor.hpp"

namespace Sea
{
    class Window;
    
    class Component : public Shape
    {
    public:
        static std::shared_ptr<Component> New(std::function<void(Component&)> on_init);
        static std::shared_ptr<Component> New(f32& relative_width, f32& relative_height);

        void Draw();
        void SetAnchor(Anchor anchor);
		void OnDraw(std::function<void()> on_draw);

        Component();
        Component(f32& relative_width, f32& relative_height);
        ~Component() = default;

    protected:
		std::function<void()> m_on_draw;
        std::function<void()> m_positionnal;
    };
    
}
