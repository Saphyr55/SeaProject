#pragma once

#include <stdint.h>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>

#include "Sea/Core/Context.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea
{	

	struct GLContext final : Context
	{

	public:
		GLContext(Window& window);
		~GLContext();

	private:
		SDL_GLContext m_handle;
		
	};

}