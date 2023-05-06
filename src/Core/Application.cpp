#include "Sea/Core/Application.hpp"
#include "Sea/Common/CommonType.hpp"
#include "Sea/Core/Clock.hpp"
#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Renderer/Window.hpp"
#include "Sea/Backend/OpenGL/Renderer/GLWindow.hpp"
#include "Sea/Core/Clock.hpp"

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

	void Application::Attach(Handler<Clock&> handler)
	{
		runner = handler;
	}

	void Application::Active(std::function<void()> run)
	{
		while (IsActive())
		{
			run();
		}
	}

	void Application::Active()
	{
		Sea::EventHandler event_handler;
		Sea::Clock clock;

		Active([&]() {

			clock.Start();

			runner(clock);

			event_handler.HandleEvent(*m_window);

			// CRITICAL LINE, free the memory
			m_window->Swap();

			// Calculate the frame rate and dt
			clock.End();
		});
	}
		
	bool Application::IsActive() 
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
		Log::Info() << "Setup context with " << Context::Tostring(GraphicAPI);
		switch (GraphicAPI)
		{
		case Sea::GraphicAPI::OpenGL:
			m_window = std::make_shared<Backend::OpenGL::GLWindow>(title, videoMode);
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
