#pragma once

#include <list>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "Sea/Core/Common.hpp"
#include "Sea/Core/List.hpp"
#include "Sea/Input/Key.hpp"
#include "Sea/Input/Mouse.hpp"

namespace Sea
{
	class EventHandler;

	class Input final
	{
	friend class EventHandler;

	public:
		static bool IsKeyDown(Key::Scancode code);
		static bool IsKeyPressed(Key::Scancode code);
		static bool IsKeyDown(Keys key);
		static bool IsKeyPressed(Keys key);
		static bool IsButtonPressed(Mouse::Button button);
		static bool IsButtonDown(Mouse::Button button);

	private:
		static void ResetKeyPressed(Keys key);
		static void ResetScancodePressed(Key::Scancode code);

	private:
		static List<Key::Scancode> scancodesPressed;
		static List<Keys> keysPressed;
	};

}