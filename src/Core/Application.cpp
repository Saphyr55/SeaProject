#include "Sea/Core/Application.hpp"
#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/Clock.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Renderer/Window.hpp"
#include "Sea/Backend/SDL/Window.hpp"

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

	void Application::Active(std::function<void()> run)
	{
		while (Active()) run();
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
		Log::Info() << "Setup context with " << Context::contextType_tostring(GraphicAPI);
		switch (GraphicAPI)
		{
		case Sea::GraphicAPI::OpenGL:
#ifndef SeaOpenGL_Context
	#define SeaOpenGL_Context
#endif
			break;
		default:
#ifndef SeaOpenGL_Context
	#define SeaOpenGL_Context
#endif
			break;
		}
		m_window = std::make_shared<Backend::SDL::Window>(title, videoMode);
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
