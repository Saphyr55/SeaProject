#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "Sea/Common/CommonType.hpp"

namespace Sea::Backend::OpenGL
{
	struct OpenGL
	{
		static void Init()
		{
			// CONFIGURE OPENGL ATTRIBUTES USING SDL:
			int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
			#ifdef _DEBUG 
				context_flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
			#endif
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			// Request an OpenGL 4.5 context (should be core)
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
			// Also request a depth buffer
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		}
	};

}