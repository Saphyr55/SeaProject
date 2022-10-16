#pragma once

#include <stdint.h>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <Sea/Core/Context.hpp>

namespace Sea::Backend::OpenGL
{	

	class GLContext final : public Context
	{

	public:

		inline GLContext(SDL_GLContext* gl_context) : m_handle(gl_context) 
		{
			if (m_handle == nullptr) throw("Failed to create OpenGL context");
		}
		
		inline ~GLContext()
		{
			SDL_GL_DeleteContext(m_handle);
		}

	private:
		SDL_GLContext m_handle;
		
	};

}