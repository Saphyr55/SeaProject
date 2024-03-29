#pragma once

#include <memory>
#include <vector>

#include "Sea/Input/Input.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

#include <SDL2/SDL.h>

namespace Sea
{	

	class EventHandler final : public Handler<Application&>
	{
	friend class Input;

	public:
		EventHandler();
		void Handle(Application& app);
		void ClearEvent();

	private:
		bool mousefirst = true;
		bool mouseMotion = false;
		SDL_Event m_handle;
	};


}