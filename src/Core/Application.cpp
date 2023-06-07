#include "Sea/Core/Application.hpp"
#include "Sea/Core/Common.hpp"
#include "Sea/Core/Clock.hpp"
#include "Sea/Graphic/OpenGL/GL.hpp"
#include "Sea/Graphic/OpenGL/Renderer/GLWindow.hpp"
#include "Sea/Graphic/Rendering/Window.hpp"

#include <SDL2/SDL.h>

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
			m_window = std::make_shared<Backend::OpenGL::GLWindow>(title, videoMode);;
			break;
		default:
			m_window = std::make_shared<Backend::OpenGL::GLWindow>(title, videoMode);;
			break;
		}
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
