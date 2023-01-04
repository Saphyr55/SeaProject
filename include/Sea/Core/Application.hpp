#pragma once

#define OPENGL

#include <string>
#include <stdexcept>
#include <filesystem>
#include <functional>

#include <mcl/Logger.hpp>
#include <stb/stb_image.h>
#include <SDL2/SDL.h>

#include "Sea/Core/Clock.hpp"
#include "Sea/Core/VideoMode.hpp"

namespace Sea
{	
	class Factory;
	class Window;

	class Application final
	{
		friend class EventHandler;

	public:
		GraphicsAPI GraphicAPI = GraphicsAPI::OpenGL;

	public:
		bool Active();
		Window& CreateWindow(std::string_view title, VideoMode& videoMode);

	private:
		void Init();

	public:
		Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		~Application();

	private:
		Ref<Window> m_window;
		bool m_isRunning = false;
	};
}