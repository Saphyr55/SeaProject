#pragma once

#include <memory>
#include <list>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "Sea/Common/CommonType.hpp"
#include "Sea/Common/List.hpp"

namespace Sea
{

	class Mouse final
	{
	friend class Event;

	public:
		enum class Button
		{
			Left = 1,
			Middle = 2,
			Right = 3,
			XButton1 = 4,
			XButton2 = 5,
		};

		static bool IsButtonDown(Button);
		static bool IsButtonPressed(Button);
		static glm::vec2 GetMousePosition();
		static glm::vec2 GetDesktopMousePosition();
		static glm::vec2 GetRelativeMousePosition();
		static s32 GetCurrentButton();

	private:
		static void Reset(Button);

	private:
		static List<Button> buttonsDown;
		static List<Button> buttonsPressed;
	};
}