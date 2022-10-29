#include <Sea/Core/Input/Mouse.hpp>
#include <Sea/Common/List.hpp>
#include <SDL2/SDL.h>

namespace Sea
{
	List<Mouse::Button> Mouse::buttonsDown;
	List<Mouse::Button> Mouse::buttonsPressed;
	f32 Mouse::RelativePosX = 0;
	f32 Mouse::RelativePosY = 0;
	s32 Mouse::PosX = 0;
	s32 Mouse::PosY = 0;

	bool Mouse::IsMouseMoved()
	{
		return Mouse::RelativePosX != 0;
	}

	bool Mouse::IsButtonDown(Button button)
	{
		return Lists::Contains(buttonsDown, button);
	}

	bool Mouse::IsButtonPressed(Button button)
	{
		if (IsButtonDown(button) && !Lists::Contains(buttonsPressed, button))
		{
			buttonsPressed.push_back(button);
			return true;
		}
		return false;
	}

	glm::vec2 Mouse::GetMousePosition()
	{	
		s32 x, y;
		SDL_GetMouseState(&x, &y);
		return glm::vec2(x,y);
	}

	glm::vec2 Mouse::GetDesktopMousePosition()
	{
		s32 x, y;
		SDL_GetGlobalMouseState(&x, &y);
		return glm::vec2(x, y);
	}

	glm::vec2 Mouse::GetRelativeMousePosition()
	{
		return glm::vec2(RelativePosX, RelativePosY);
	}

	s32 Mouse::GetCurrentButton()
	{
		return SDL_GetGlobalMouseState(nullptr, nullptr);
	}

	void Mouse::Reset(Button button)
	{
		if (Lists::Contains(buttonsPressed, button)) buttonsPressed.remove(button);
	}

}