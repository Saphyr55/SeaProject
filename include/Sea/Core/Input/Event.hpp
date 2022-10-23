#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <functional>
#include <vector>

namespace Sea
{	
	class Game;
	using Callback = std::function<void(void)>;

	class Event final
	{
		friend class Input;

	public:
		void HandleEvent(Game& game);

	private:
		SDL_Event m_handle;
	};
}