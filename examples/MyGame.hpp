#pragma once

#include <iostream>
#include <Sea/Core/Game.hpp>

class MyGame final : public Sea::Game
{
public:
	void OnRender() override;
	void OnUpdate(float dt) override;

private:
};

void MyGame::OnRender()
{
	std::cout << "DS\n";
}


void MyGame::OnUpdate(float dt)
{

}