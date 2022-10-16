#pragma once

#include <Sea/Common/CommonType.hpp>

namespace Sea
{
    struct Color;

    struct Colors
    {
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Black;
        static const Color White;
    };

    struct Color
    {

    public:
        Color(f32 r, f32 g, f32 b, f32 a) : r(r), g(g), b(b), a(a) {}
        ~Color() = default;

    public:
        f32 r, g, b, a;
    };


    const Color Colors::Red(1.f, 0.f, 0.f, 1.f);
    const Color Colors::Green(0.f, 1.f, 0.f, 1.f);
    const Color Colors::Blue(0.f, 0.f, 1.f, 1.f);
    const Color Colors::Black(0.f, 0.f, 0.f, 1.f);
    const Color Colors::White(1.f, 1.f, 1.f, 1.f);


}