#pragma once

#include "Sea/Renderer/Window.hpp"

namespace Sea::Backend::OpenGL
{
	class GLWindow final : public Window
	{
	public:
		GLWindow(std::string title, std::uint32_t width, std::uint32_t height);

	private:

	};

}