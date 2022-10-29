#include "Sea/Core/Input/Event.hpp"
#include "Sea/Core/Input/Input.hpp"
#include "Sea/Core/Application.hpp"
#include "Sea/Core/Game.hpp"
#include "mcl/Logger.hpp"
#include "Sea/Core/Input/Key.hpp">

using mcl::Log;

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
				Mouse::buttonsDown.push_back((Mouse::Button)m_handle.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				Mouse::Reset((Mouse::Button)m_handle.button.button);
				Mouse::buttonsDown.remove((Mouse::Button)m_handle.button.button);
				break;
			case SDL_MOUSEMOTION:
				Mouse::RelativePosY = (f32) m_handle.motion.yrel;
				Mouse::RelativePosX = (f32) m_handle.motion.xrel;
				Mouse::PosX = m_handle.motion.x;
				Mouse::PosY = m_handle.motion.y;
				break;
			default:
				break;
			}

		}

	}

}