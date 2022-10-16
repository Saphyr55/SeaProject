#pragma once

#include <memory>
#include "Sea/Renderer/Window.hpp"
#include "Sea/Context.hpp"
#include "Sea/Core/Game.hpp"

namespace Sea
{

	class Sea
	{
	public:
		void Run();
		void CreateWindow(std::string title, std::uint32_t w, std::uint32_t h);

	private:
		inline void Close() { m_isRunning = false; }

	public:
		Sea(ContextType context, Game game);
		Sea(Game game);
		~Sea();

	private:
		bool m_isRunning;
		std::unique_ptr<Context> m_context;
		std::unique_ptr<Window> m_window;
		Game m_game;
	};
}