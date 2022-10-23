#pragma once

#include <list>
#include <SDL2/SDL.h>
#include "Sea/Core/Input/Key.hpp"
#include "Sea/Common/CommonType.hpp"

namespace Sea
{
	class Event;

	class Input final
	{
		friend class Event;

	public:
		static bool IsKeyDown(Key::Scancode code);
		static bool IsKeyPressed(Key::Scancode code);
		static bool IsKeyDown(Key::Keys key);
		static bool IsKeyPressed(Key::Keys key);
	
	private:
		static void ResetKeyPressed(Key::Keys key);
		static void ResetScancodePressed(Key::Scancode code);

	private:
		static std::list<Key::Scancode> scancodesPressed;
		static std::list<Key::Keys> keysPressed;
	};

}