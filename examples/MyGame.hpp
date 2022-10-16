#pragma once

#include <iostream>
#include <Sea/Core/Game.hpp>

class MyGame : public Sea::Game
{
public:
	void OnRender()
	{
		std::cout << "Salut\n";
	}

	void OnUpdate(float dt)
	{

	}

private:
};
