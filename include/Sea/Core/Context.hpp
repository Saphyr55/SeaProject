#pragma once

#include <stdint.h>
#include <memory>
#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <Sea/Common/CommonType.hpp>

namespace Sea
{

	enum class ContextType
	{
		OpenGL
	};

	class Context
	{
	public:
		static std::string contextType_tostring(ContextType context)
		{
			switch (context)
			{
			case ContextType::OpenGL:
				return "OpenGL";
			default:
				break;
			}
			return "unknown graphic API";
		}

	public:
		Context() = default;
		~Context() = default;
	};



}