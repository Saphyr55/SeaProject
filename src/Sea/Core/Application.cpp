#include <filesystem>

#include <fmt/printf.h>
#include <stb/stb_image.h>
#include <SDL2/SDL.h>

#include "Sea/Core/Application.hpp"
#include "Sea/Core/Common.hpp"
#include "Sea/Core/Clock.hpp"
#include "Sea/Core/VideoMode.hpp"
#include "Sea/Core/Handler.hpp"

namespace fs = std::filesystem;

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

	void Application::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			fmt::print("Init SDL fail\n");
			throw std::exception();
		}

		stbi_set_flip_vertically_on_load(1);
	}

	void Application::Stop()
	{
		m_is_running = false;
	}

	void Application::Launch()
	{
		m_is_running = true;
		for (auto handler : m_handlers)
		{
			handler->Handle(*this);
		}
	}

	void Application::Attach(Ref<Handler<Application&>> handler)
	{
		m_handlers.push_back(handler);
	}

	void Application::SetOnQuit(std::function<void()> onQuit)
	{
		m_on_quit = onQuit;
	}

	std::function<void()>& Application::GetOnQuit()
	{
		return m_on_quit;
	}


}
