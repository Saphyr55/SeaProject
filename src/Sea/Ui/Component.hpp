#pragma once

#define SEA_DEPTH_BETWEEN_COMPONENT 1.0E-7F

#include <functional>

#include "Sea/Core/Common.hpp"
#include "Sea/Graphics/Drawing/Shape.hpp"

namespace Sea
{
    class Window;
    class UiProperties;

    class Component : public Shape
    {
    public:
        using PropertiesInit = std::function<void(UiProperties&)>;

        static std::shared_ptr<Component> New(PropertiesInit on_init);
        static std::shared_ptr<Component> New(f32& relative_width, f32& relative_height);

        void Draw();
		void OnDraw(std::function<void()> on_draw);
        UiProperties& GetProperties();

    private:
        void Update();

    public:
        Component();
        Component(f32& relative_width, f32& relative_height);
        ~Component() = default;

    protected:
        Ref<UiProperties> m_ui_properties;
		std::function<void()> m_on_draw;
    };
    
}
