#pragma once

#include <memory>
#include "Sea/Renderer/Window.hpp"
#include "Sea/Context.hpp"
#include "Sea/Core/Game.hpp"

namespace Sea
{	
	using WindowPtr = std::shared_ptr<Window>;
	using GamePtr = std::shared_ptr<Game>;

	class Sea final
	{
	public:
		void Run();
		void CreateWindow(WindowProperties& properties);
		void CreateGame(GamePtr game);

	private:
		void Init();
		void Close();

	public:
		Sea();
		~Sea();

	private:
		WindowPtr m_window;
		GamePtr m_game;
	};
}