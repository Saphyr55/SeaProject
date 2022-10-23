#include <Sea/Core/Input/Mouse.hpp>
#include <Sea/Common/List.hpp>
#include <SDL2/SDL.h>

namespace Sea
{
	List<Mouse::Button> Mouse::buttonsDown;
	List<Mouse::Button> Mouse::buttonsPressed;
	s32 Mouse::currentButton = -1;

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

	u32 Mouse::GetMousePosX()
	{
		return u32();
	}

	u32 Mouse::GetMousePosY()
	{
		return u32();
	}

	glm::vec2 Mouse::GetMousePos()
	{
		return glm::vec2();
	}

	glm::vec2 Mouse::GetMouseRelativePos()
	{
		return glm::vec2();
	}

	u32 Mouse::GetCurrentButton()
	{
		return currentButton;
	}

	void Mouse::Reset(Button button)
	{
		if (Lists::Contains(buttonsPressed, button)) buttonsPressed.remove(button);
	}

}