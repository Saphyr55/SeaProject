#include <iostream>
#include <Sea/Core/Engine.hpp>
#include <Sea/Renderer/Window.hpp>
#include <Sea/Core/Context.hpp>
#include "MyGame.hpp"

int main(int argc, char const **argv)
{
	try
	{
		Engine sea;
		Window::Properties propeties;
		{
			propeties.title = "Game";
			propeties.width = 880;
			propeties.height = 620;
			propeties.context = ContextType::OpenGL;
		}

		MyGame mg;
		sea.CreateGameWindow(std::make_unique<MyGame>(mg), propeties);
		sea.Run();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
