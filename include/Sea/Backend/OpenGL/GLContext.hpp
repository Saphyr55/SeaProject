#pragma once

#include <stdint.h>
#include <string>
#include <SDL2/SDL.h>
#include <Sea/Context.hpp>

namespace Sea::Backend::OpenGL
{	

	class GLContext final : public Context
	{

	public:
		std::unique_ptr<Window> CreateWindow(std::string title, std::uint32_t w, std::uint32_t h);

		GLContext() = default;
		~GLContext() = default;
	};

}