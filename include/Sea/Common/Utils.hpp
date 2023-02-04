#pragma once

#include "Sea/Common/CommonType.hpp"

namespace Sea
{
	f32 Clamp(f32 value, f32 min, f32 max)
	{
		if (value > max) value = max;
		if (value < min) value = min;
		return value;
	}
}