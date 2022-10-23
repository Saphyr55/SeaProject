#include "Sea/Core/Input/Input.hpp"
#include <iostream>

namespace Sea
{
	std::list<Key::Scancode> Input::scancodesPressed;
	std::list<Key::Keys> Input::keysPressed;

	bool Input::IsKeyDown(Key::Scancode code)
	{	
		return SDL_GetKeyboardState(NULL)[(SDL_Scancode)(u32)code];
	}

	bool Input::IsKeyPressed(Key::Scancode code)
	{	
		if (std::find(scancodesPressed.begin(), scancodesPressed.end(), code) == scancodesPressed.end() && IsKeyDown(code))
		{
			scancodesPressed.push_back(code);
			return true;
		}
		return false;
	}

	bool Input::IsKeyDown(Key::Keys key)
	{
		return IsKeyDown((Key::Scancode)(u32)SDL_GetScancodeFromKey((SDL_KeyCode)(s32)key));
	}

	bool Input::IsKeyPressed(Key::Keys key)
	{
		if (std::find(keysPressed.begin(), keysPressed.end(), key) == keysPressed.end() && IsKeyDown(key))
		{
			keysPressed.push_back(key);
			return true;
		}
		return false;
	}

	void Input::ResetKeyPressed(Key::Keys key)
	{
		if (std::find(Input::keysPressed.begin(), Input::keysPressed.end(), key) != Input::keysPressed.end())
		{
			Input::keysPressed.remove(key);
		}
	}

	void Input::ResetScancodePressed(Key::Scancode code)
	{
		if (std::find(Input::scancodesPressed.begin(), Input::scancodesPressed.end(), code) != Input::scancodesPressed.end())
		{
			Input::scancodesPressed.remove(code);
		}
	}


}