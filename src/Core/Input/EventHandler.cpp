#include "Sea/Core/Input/EventHandler.hpp"
#include "Sea/Core/Input/Input.hpp"
#include "Sea/Core/Input/Key.hpp">
#include <mcl/Logger.hpp>

using mcl::Log;

namespace Sea
{

	void EventHandler::HandleEvent()
	{
		while (SDL_PollEvent(&m_handle))
		{
			Mouse::IsMoved = (m_handle.type == SDL_MOUSEMOTION) ? true : false;

			switch (m_handle.type)
			{
			case SDL_QUIT:
				m_window->Close();
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
				for (auto callback : Mouse::callbacks)
					callback();
				Mouse::RelativePosY = m_handle.motion.yrel;
				Mouse::RelativePosX = m_handle.motion.xrel;
				Mouse::PosX = m_handle.motion.x;
				Mouse::PosY = m_handle.motion.y;
				break;
			default:
				break;
			}

			SDL_PumpEvents();
		}
		ClearEvent();
	}

	void EventHandler::ClearEvent()
	{
		Mouse::callbacks.clear();
	}

}