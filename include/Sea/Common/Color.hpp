#pragma once

#include <iostream>
#include <Sea/Common/CommonType.hpp>

namespace Sea
{
    struct Color;

    struct Colors final
    {
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Black;
        static const Color White;
        static const Color Nothing;
    };

    struct Color final
    {
        Color(f32 r, f32 g, f32 b, f32 a) : r(r), g(g), b(b), a(a) {}
        ~Color() = default;

        std::ostream& operator<<(std::ostream& outs)
        {
            return outs << "(" << r << "," << g << "," << b << "," << a <<")";
        }

        f32 r, g, b, a;
    };

}