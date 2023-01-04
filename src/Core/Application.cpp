#include "Sea/Core/Application.hpp"
#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/Mold.hpp"
#include "Sea/Core/Clock.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Core/Factory.hpp"
#include "Sea/Renderer/Window.hpp"

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

	bool Application::Active()
	{
		if (!m_isRunning)
		{
			m_isRunning = true;
			m_window->Run();
		}
		m_window->Update();
		return m_isRunning && m_window->IsOpen();
	}

	Window& Application::CreateWindow(std::string_view title, VideoMode& videoMode)
	{	
		Molder::API = GraphicAPI;
		Log::Info() << "Setup context with " << Context::contextType_tostring(GraphicAPI);
		m_window = Factory::CreateWindow(title, videoMode);
		return *m_window;
	}

	void Application::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			Log::Error() << "Init SDL fail";
			throw std::exception();
		}

		stbi_set_flip_vertically_on_load(1);
	}





}
