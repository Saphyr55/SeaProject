#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <Sea/Common/CommonType.hpp>

namespace Sea
{
	class Window;
	struct WindowProperties;

	enum struct ContextType
	{
		OpenGL
	};

	class Context
	{
	public:
		Context() { }
		~Context() = default;
	};

}