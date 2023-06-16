#pragma once

#include <cmath>

#include "Sea/Math/Matrix4.hpp"
#include "Sea/Math/Vector2.hpp"
#include "Sea/Math/Vector3.hpp"
#include "Sea/Math/Vector4.hpp"

namespace Sea
{
    template<typename T>
    T Abs(T n)
    {
        if (n < 0) return -n;
        return n;
    }

    template<typename T>
    float Sqrt(T n)
    {
        return std::sqrt(n);
    }

}
