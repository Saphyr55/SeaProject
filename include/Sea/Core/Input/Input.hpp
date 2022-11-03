#pragma once

#include <list>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "Sea/Common/List.hpp"
#include "Sea/Core/Input/Key.hpp"
#include "Sea/Core/Input/Mouse.hpp"
#include "Sea/Common/CommonType.hpp"

namespace Sea
{
	class EventHandler;

	class Input final
	{
	friend class EventHandler;

	public:
		static bool IsKeyDown(Key::Scancode code);
		static bool IsKeyPressed(Key::Scancode code);
		static bool IsKeyDown(Key::Keys key);
		static bool IsKeyPressed(Key::Keys key);
		static bool IsButtonPressed(Mouse::Button button);
		static bool IsButtonDown(Mouse::Button button);

	private:
		static void ResetKeyPressed(Key::Keys key);
		static void ResetScancodePressed(Key::Scancode code);

	private:
		static List<Key::Scancode> scancodesPressed;
		static List<Key::Keys> keysPressed;
	};

}