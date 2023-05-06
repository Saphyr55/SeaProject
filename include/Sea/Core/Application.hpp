#pragma once

#include <string>
#include <stdexcept>
#include <filesystem>
#include <functional>

#include "Sea/Core/Clock.hpp"
#include "Sea/Core/VideoMode.hpp"
#include "Sea/Renderer/Window.hpp"

#include <mcl/Logger.hpp>
#include <stb/stb_image.h>
#include <SDL2/SDL.h>


namespace Sea
{	
	class Clock;

	class Application final
	{
		friend class EventHandler;

	public:
		GraphicAPI GraphicAPI = GraphicAPI::OpenGL;

	public:
		void Attach(Handler<Clock&> handler);
		void Active();
		bool IsActive();
		void Active(std::function<void()> run);
		Window& CreateWindow(std::string_view title, VideoMode& videoMode);

	private:
		void Init();

	public:
		Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		~Application();

	private:
		Handler<Clock&> runner;
		Ref<Window> m_window;
		bool m_isRunning = false;
	};
}