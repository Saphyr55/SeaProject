#pragma once

#include <memory>
#include "Sea/Renderer/Window.hpp"
#include "Sea/Context.hpp"
#include "Sea/Core/Game.hpp"

namespace Sea
{

	class Sea final
	{
	public:
		void Run();
		void CreateWindow(std::string title, std::uint32_t w, std::uint32_t h);

	private:
		void Close();

	public:
		Sea(ContextType context, Game game);
		Sea(Game game);
		~Sea();

	private:
		std::unique_ptr<Context> m_context;
		std::unique_ptr<Window> m_window;
		Game m_game;
	};
}