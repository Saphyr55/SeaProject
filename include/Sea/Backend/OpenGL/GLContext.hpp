#pragma once

#include <stdint.h>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <Sea/Core/Context.hpp>
#include <Sea/Backend/SDL/Window.hpp>

namespace Sea::Backend::OpenGL
{	

	struct GLContext final : Context
	{

	public:
		GLContext(::Sea::Backend::SDL::Window& window);
		~GLContext();

	private:
		SDL_GLContext m_handle;
		
	};

}