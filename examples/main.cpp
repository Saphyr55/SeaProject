#include <iostream>

#include <Sea/Core/Application.hpp>

#include "MyGame.hpp"

int main(int argc, char const **argv)
{
	try
	{
		// fs::current_path().fs::path::parent_path()).string();
		File::FROM_SOURCE = "../../";
		Application sea;

		Window::Properties propeties;
		{
			propeties.Context = ContextType::OpenGL;
			propeties.Title = "Game";
			propeties.FileIcon = "./examples/res/icon.png";
			propeties.Width = 880;
			propeties.Height = 620;
			propeties.Resizable = true;
		}

		sea.CreateGameWindow(std::make_shared<MyGame>(), propeties);
		sea.Run();
	}
	catch (const std::exception &e)
	{
		Log::Error() << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
