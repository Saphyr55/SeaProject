#include <SDL2/SDL.h>
#include <stdexcept>

#include "Sea/Sea.hpp"
#include "Sea/Backend/OpenGL/GLWindow.hpp"

namespace Sea
{
	void Sea::CreateWindow()
	{
		
	}

	void Sea::OnUpdate(float dt)
	{
		m_window.OnUpdate(dt);
	}

	void Sea::Run()
	{
		while (m_isRunning)
		{
			while (m_window.IsOpen())
			{
				
			}
		}
	}

	Sea::Sea(ContextType context, Window& window)
		: m_context(context), m_isRunning(true), m_window(window)
	{
		
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
			throw std::runtime_error("Init SDL fail");
	}

	Sea::~Sea()
	{
		SDL_Quit();
	}

}
