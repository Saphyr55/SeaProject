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
			propeties.context = ContextType::OpenGL;
			propeties.title = "Game";
			propeties.width = 880;
			propeties.height = 620;
			propeties.resizable = true;
		}
		
		sea.CreateGameWindow(std::make_unique<MyGame>(), propeties);
		sea.Run();
	}
	catch (const std::exception &e)
	{
		Log::Error() << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
