#include <SDL2/SDL.h>
#include <stdexcept>

#include "Sea/Core/Engine.hpp"

namespace Sea
{

	Engine::Engine()
	{ 
		Init(); 
	}

	Engine::~Engine()
	{ 
		SDL_Quit(); 
	}

	void Engine::CreateGameWindow(std::shared_ptr<Game> game, Window::Properties& properties)
	{ 
		m_game = game;
		m_game->m_window = Window::Of(properties);
	}

	void Engine::Before()
	{
		if (m_game)
		{
			m_game->Run();
			m_game->Before();
		}
	}

	void Engine::After()
	{
		if (m_game)
		{
			m_game->After();
		}
	}

	void Engine::Running()
	{
		while (m_game->IsRunning())
		{
			m_game->GetWindow().CreateEvent();
			
			while (m_game->GetWindow().IsOpen())
			{
				m_game->GetWindow().Swap();
				m_game->Update(60);
				m_game->Render();
				m_game->GetWindow().m_event->HandleEvent(*m_game);
			}
		}
	}

	void Engine::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw std::runtime_error("Init SDL fail");
	}

	void Engine::Run()
	{	
		Before();
		Running();
		After();
	}



}
