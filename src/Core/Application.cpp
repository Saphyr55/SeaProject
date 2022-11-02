

#include "Sea/Core/Application.hpp"

#include <mcl/Logger.hpp>
#include <stb/stb_image.h>
#include <SDL2/SDL.h>

#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;
using mcl::Log;

namespace Sea
{

	Application::Application()
	{ 
		Init();
	}

	Application::~Application()
	{ 
		SDL_Quit(); 
	}

	void Application::Run()
	{
		Before();
		Running();
		After();
	}

	void Application::CreateGameWindow(std::shared_ptr<Game> game, Window::Properties& properties)
	{	
		m_game = game;
		m_game->m_window = Window::Of(properties);
	}

	void Application::Before()
	{
		if (m_game)
		{
			m_game->Run();
			m_game->Before();
			m_game->GetRenderer().Enable();
		}
	}

	void Application::After()
	{
		if (m_game)
		{
			m_game->After();
		}
	}

	void Application::Running()
	{	
		while (m_game->IsRunning())
		{
			m_game->GetWindow().CreateEvent();
			m_clock.Last = m_clock.GetTicks();
			while (m_game->GetWindow().IsOpen())
			{
				m_clock.StartTick(*m_game);
				m_game->StartFPS();
				m_game->GetWindow().m_event->ClearEvent();
				m_game->GetWindow().Update();
				m_game->Render();
				m_game->Update(m_clock.Delta);
				m_game->GetWindow().m_event->HandleEvent(*m_game);
				m_game->EndFPS();
				m_game->GetWindow().Swap();
				m_clock.EndTick();
			}

		}
	}

	void Application::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
			throw std::runtime_error("Init SDL fail");

		stbi_set_flip_vertically_on_load(1);
	}





}
