#include <SDL2/SDL.h>
#include <stdexcept>

#include "Sea/Sea.hpp"

namespace Sea
{

	Sea::Sea()
	{
		Init();
	}

	Sea::~Sea() 
	{ 
		SDL_Quit(); 
	}

	void Sea::CreateWindow(WindowProperties& properties)
	{
		m_window = Window::Of(properties);
	}

	void Sea::CreateGame(GamePtr game)
	{	
		m_game = game;
	}

	void Sea::Close()
	{
		m_window->Close();
		m_game->Stop();
	}

	void Sea::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw std::runtime_error("Init SDL fail");
	}

	void Sea::Run()
	{	
		if (m_window != nullptr) m_window->Run();
		if (m_game != nullptr) m_game->Run();
		while (m_game->IsRunning())
		{	
			SDL_Event event;

			while (m_window->IsOpen())
			{
				m_game->OnUpdate(60);
				m_game->OnRender();
				
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_QUIT:
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
