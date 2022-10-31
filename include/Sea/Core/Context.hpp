#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <Sea/Common/CommonType.hpp>

namespace Sea
{

	enum struct ContextType
	{
		OpenGL
	};

	class Context
	{
	public:
		Context() = default;
		~Context() = default;
	};

}