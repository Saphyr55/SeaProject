#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

namespace Sea
{	
	class Game;

	class Event final
	{
	friend class Input;

	public:
		void HandleEvent(Game& game);
		void ClearEvent();

	private:
		bool mousefirst = true;
		bool mouseMotion = false;
		SDL_Event m_handle;
	};


}