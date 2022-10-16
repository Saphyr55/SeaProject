#include <iostream>
#include <Sea/Sea.hpp>
#include <Sea/Renderer/Window.hpp>
#include <Sea/Context.hpp>
#include "MyGame.hpp"

int main(int argc, char const **argv)    
{   
	try
	{	
		Sea::Sea sea = Sea::Sea(Sea::ContextType::OpenGL, MyGame());
		sea.CreateWindow("Game", 900, 720);
		sea.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
    return EXIT_SUCCESS;
}


