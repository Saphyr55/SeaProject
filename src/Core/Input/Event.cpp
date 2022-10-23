#include "Sea/Core/Input/Event.hpp"
#include "Sea/Core/Input/Input.hpp"
#include "Sea/Core/Engine.hpp"
#include "Sea/Core/Game.hpp"
#include "mcl/Logger.hpp"
#include "Sea/Core/Input/Key.hpp">

namespace Sea
{
	
	void Event::HandleEvent(Game& game)
	{

		while (SDL_PollEvent(&m_handle))
		{	
			SDL_PumpEvents();
			
			switch (m_handle.type)
			{
			case SDL_QUIT:
				game.Stop();
				break;
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				Input::ResetScancodePressed((Key::Scancode)((u32)m_handle.key.keysym.scancode));
				Input::ResetKeyPressed((Key::Keys)((s32)m_handle.key.keysym.sym));
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			default:
				break;
			}

		}

	}

}