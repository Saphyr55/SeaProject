#pragma once

#include "Sea/Core/Context.hpp"
#include "Sea/Core/Game.hpp"
#include "Sea/Core/Clock.hpp"
#include "Sea/Renderer/Window.hpp"

namespace Sea
{	

	class Application final
	{
	friend class Event;

	public:
		void Run();
		void CreateGameWindow(std::shared_ptr<Game> game, Window::Properties& properties);

	private:
		void Init();
		void Before();
		void After();
		void Running();

	public:
		Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		~Application();

	private:
		Clock m_clock;
		std::shared_ptr<Game> m_game;
	};
}