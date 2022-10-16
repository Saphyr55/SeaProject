#include <iostream>
#include <Sea/Sea.hpp>
#include <Sea/Renderer/Window.hpp>
#include <Sea/Context.hpp>
#include "MyGame.hpp"

int main(int argc, char const **argv)
{
	try
	{

		Sea::WindowProperties propeties;
		propeties.title = "Game";
		propeties.width = 900;
		propeties.height = 720;
		propeties.context = Sea::ContextType::OpenGL;

		MyGame mg;
		Sea::Sea sea;
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
