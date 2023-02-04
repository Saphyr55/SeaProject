#pragma once

#include <stdint.h>
#include <memory>
#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/VideoMode.hpp"

namespace Sea
{

	struct Context
	{
		static std::string contextType_tostring(GraphicAPI api)
		{
			switch (api)
			{
			case GraphicAPI::OpenGL:
				return "OpenGL";
			default:
				break;
			}
			return "unknown graphic API";
		}

		Context()=default;
		~Context()=default;
	};
}