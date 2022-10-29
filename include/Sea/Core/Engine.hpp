#pragma once

#include "Sea/Core/Context.hpp"
#include "Sea/Core/Game.hpp"
#include "Sea/Renderer/Window.hpp"

namespace Sea
{	

	class Engine final
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
		Engine();
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		~Engine();

	private:
		std::shared_ptr<Game> m_game;
	};
}