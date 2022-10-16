#pragma once

#include <iostream>
#include <Sea/Core/Game.hpp>
#include <Sea/Common/Color.hpp>

class MyGame final : public Sea::Game
{
public:
	void OnRender(Sea::Renderer& renderer) override;
	void OnUpdate(float dt) override;

private:
};

void MyGame::OnRender(Sea::Renderer& renderer)
{
	renderer.ClearColor(Sea::Colors::Black);
	renderer.Clear();
}


void MyGame::OnUpdate(float dt)
{

}