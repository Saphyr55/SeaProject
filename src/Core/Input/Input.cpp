#include "Sea/Core/Input/Input.hpp"
#include "Sea/Core/Input/Mouse.hpp"
#include <iostream>

namespace Sea
{
	List<Key::Scancode> Input::scancodesPressed;
	List<Keys> Input::keysPressed;

	bool Input::IsKeyDown(Key::Scancode code)
	{	
		return SDL_GetKeyboardState(NULL)[(SDL_Scancode)(u32)code];
	}

	bool Input::IsKeyPressed(Key::Scancode code)
	{	
		if (!Lists::Contains(scancodesPressed, code) && IsKeyDown(code))
		{
			scancodesPressed.push_back(code);
			return true;
		}
		return false;
	}

	bool Input::IsKeyDown(Keys key)
	{
		return IsKeyDown((Key::Scancode)(u32)SDL_GetScancodeFromKey((SDL_KeyCode)(s32)key));
	}

	bool Input::IsKeyPressed(Keys key)
	{
		if (!Lists::Contains(keysPressed, key) && IsKeyDown(key))
		{
			keysPressed.push_back(key);
			return true;
		}
		return false;
	}

	bool Input::IsButtonPressed(Mouse::Button button)
	{
		return Mouse::IsButtonPressed(button);
	}

	bool Input::IsButtonDown(Mouse::Button button)
	{
		return Mouse::IsButtonDown(button);
	}

	void Input::ResetKeyPressed(Keys key)
	{
		if (Lists::Contains(keysPressed, key)) Input::keysPressed.remove(key);
	}

	void Input::ResetScancodePressed(Key::Scancode code)
	{
		if (Lists::Contains(scancodesPressed, code)) Input::scancodesPressed.remove(code);
	}


}