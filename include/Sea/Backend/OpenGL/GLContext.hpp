#pragma once

#include <stdint.h>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <Sea/Core/Context.hpp>
#include <Sea/Renderer/Window.hpp>

namespace Sea::Backend::OpenGL
{	

	class GLContext final : public Context
	{

	public:
		GLContext(Window& window);
		~GLContext();

	private:
		SDL_GLContext m_handle;
		
	};

}