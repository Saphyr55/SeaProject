#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <SDL2/SDL.h>

namespace Sea
{
	class Window;

	enum struct ContextType
	{
		OpenGL
	};

	class Context
	{
	public:
		static std::unique_ptr<Context> Of(ContextType contextType);

	public:
		virtual std::unique_ptr<Window> CreateWindow(std::string title, std::uint32_t w, std::uint32_t h) abstract;

	public:
		Context() = default;
		~Context() = default;
	};

}