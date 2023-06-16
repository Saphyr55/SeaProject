#include <SDL2/SDL.h>
#include <fmt/printf.h>

#include "Sea/Input/Mouse.hpp"
#include "Sea/Core/List.hpp"

namespace Sea
{
	void Mouse::ShowCursor(bool show)
	{
		SDL_ShowCursor((show) ? SDL_ENABLE : SDL_DISABLE);
	}

	void Mouse::SetRelativeMouseMode(bool active)
	{
		if (SDL_SetRelativeMouseMode((active) ? SDL_TRUE : SDL_FALSE) == -1)
		{
			fmt::printf("Relative Mouse Mode not supported\n");
		}
	}

	void Mouse::OnMoved(std::function<void(void)> callback)
	{
		callbacks.push_back(callback);
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
		s32 x, y;
		SDL_GetRelativeMouseState(&x, &y);
		return glm::vec2(x, y);
	}

	s32 Mouse::GetCurrentButton()
	{
		return SDL_GetGlobalMouseState(nullptr, nullptr);
	}

	void Mouse::Reset(Button button)
	{
		if (Lists::Contains(buttonsPressed, button)) buttonsPressed.remove(button);
	}

	List<Mouse::Button> Mouse::buttonsDown;
	List<Mouse::Button> Mouse::buttonsPressed;
	f32 Mouse::RelativePosX = 0;
	f32 Mouse::RelativePosY = 0;
	s32 Mouse::PosX = 0;
	s32 Mouse::PosY = 0;
	bool Mouse::IsMoved = false;
	List<std::function<void(void)>> Mouse::callbacks;

}