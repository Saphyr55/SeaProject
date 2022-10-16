#include <iostream>
#include <Sea/Core/Sea.hpp>
#include <Sea/Renderer/Window.hpp>
#include <Sea/Core/Context.hpp>
#include "MyGame.hpp"


int main(int argc, char const **argv)
{
	try
	{
		Sea::Sea sea;
		Sea::WindowProperties propeties;
		{
			propeties.title = "Game";
			propeties.width = 900;
			propeties.height = 720;
			propeties.context = Sea::ContextType::OpenGL;
		}

		MyGame mg;
		sea.CreateGame(std::make_shared<MyGame>(mg));
		sea.CreateWindow(propeties);
		sea.Run();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
