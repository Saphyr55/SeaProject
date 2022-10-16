#pragma once

#include "Sea/Renderer/Window.hpp"

namespace Sea::Backend::OpenGL
{
	class GLWindow final : public Window
	{
	public:
		void Run();
		void Swap();

	private:
		void CreateContext();

	public:
		GLWindow(WindowProperties& properties);


	private:
		SDL_GLContext gl_context;
	};

}