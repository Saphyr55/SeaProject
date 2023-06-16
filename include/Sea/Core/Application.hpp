#pragma once

#include <string>
#include <stdexcept>
#include <filesystem>
#include <functional>

#include <stb/stb_image.h>

#include "Sea/Core/Clock.hpp"
#include "Sea/Core/VideoMode.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea
{	
	class Application final
	{
		friend class EventHandler;

	public:
		GraphicAPI GraphicAPI = GraphicAPI::OpenGL;
		
	public:
		bool Active();
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
		Ref<Window> m_window;
		bool m_isRunning = false;
	};
}