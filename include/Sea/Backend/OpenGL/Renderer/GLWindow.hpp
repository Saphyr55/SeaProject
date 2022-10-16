#pragma once

#include "Sea/Renderer/Window.hpp"

namespace Sea::Backend::OpenGL
{
	class GLWindow final : public Window
	{
	public:
		void Run();

	public:
		GLWindow(WindowProperties& properties);

	private:

	};

}