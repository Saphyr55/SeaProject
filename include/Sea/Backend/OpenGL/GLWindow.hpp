#pragma once

#include <Sea/Core/GameWindow.hpp>

namespace Sea::Backend::OpenGL
{
	class GLWindow : public GameWindow
	{
	public:
		GLWindow(std::string title, int width, int height);
	};

}