#pragma once

#include "Sea/Renderer/Window.hpp"

namespace Sea::Backend::OpenGL
{
	class GLWindow final : public Window
	{
	public:
		void Run();
		void Swap();
		void UseVSync(bool use);

	public:
		GLWindow(Window::Properties& properties);

	};

}