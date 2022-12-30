#pragma once

#include <cmath>

namespace Sea
{
    template<typename T>
    T Abs(T n)
    {
        if (n < 0) return -n;
        return n;
    }

    template<typename T>
    T Sqrt(T n)
    {
        return std::sqrt(n);
    }

}
