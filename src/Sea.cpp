#include <SDL2/SDL.h>
#include <stdexcept>

#include "Sea/Sea.hpp"

namespace Sea
{

	Sea::Sea(ContextType context, Game game)
		: m_isRunning(true), m_context(Context::Of(context)), m_game(game)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw std::runtime_error("Init SDL fail");
	}

	Sea::Sea(Game game) : Sea::Sea(ContextType::OpenGL, game) { }

	Sea::~Sea()
	{
		SDL_Quit();
	}

	void Sea::CreateWindow(std::string title, std::uint32_t w, std::uint32_t h)
	{
		m_window = m_context.get()->CreateWindow(title, w, h);
	}

	void Sea::Run()
	{	
		while (m_isRunning)
		{	
			while (m_window.get()->IsOpen())
			{
				SDL_Event event;

				m_game.OnUpdate(60);
				m_game.OnRender();
				
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_QUIT:
						m_window.get()->Close();
						Close();
						break;
					default:
						break;
					}
				}
			}
		}
	}



}
