#pragma once

#include <iostream>
#include <Sea/Common/CommonType.hpp>
#include <glm/glm.hpp>

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
        static const Color Aqua;
        static const Color Azure;
        static const Color AliceBlue;
        static const Color Emerald;
		static const Color Pink;
		static const Color Crimson;
		static const Color Yellow; 
		static const Color CarolinaBlue;
		static const Color GraniteGray;
		static const Color Gray;
		static const Color LapisLazuli;
		static const Color Mauve;
		static const Color Strawberry;
		static const Color Silver;
		static const Color Wheat;
		static const Color Violet;
        static const Color EerieBlack;
    };

    struct Color final
    {
        Color(f32 r, f32 g, f32 b, f32 a) : r(r), g(g), b(b), a(a) {}
        ~Color() = default;

        const glm::vec3 toVec3f() const
        {
            return glm::vec3(r,g,b);
        }
		
        const glm::vec4 toVec4f() const
		{
			return glm::vec4(toVec3f(), a);
		}

        std::ostream& operator<<(std::ostream& outs)
        {
            return outs << "(" << r << "," << g << "," << b << "," << a <<")";
        }

        f32 r, g, b, a;
    };

}