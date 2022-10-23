#pragma once

#include <iostream>
#include <Sea/Core/Game.hpp>
#include <Sea/Core/Input/Input.hpp>
#include <Sea/Common/Color.hpp>
#include <mcl/Logger.hpp>

using namespace Sea;
using Log = mcl::Log;

class MyGame final : public Game
{

public:
	void Render() override;
	void Update(float dt) override;
	void Before() override;
	void After() override;

private:

};

void MyGame::Before()
{

}

void MyGame::After()
{

}

void MyGame::Render()
{
	GetWindow().GetRenderer().ClearColor(Colors::Red);
	GetWindow().GetRenderer().Clear();
}


void MyGame::Update(float dt)
{
	if (Input::IsKeyDown(Key::Keys::Q))
	{
		Log::Debug() << "Q";
	}

	if (Input::IsKeyPressed(Key::Keys::S))
	{
		Log::Debug() << "S";
	}

	if (Input::IsKeyPressed(Key::Keys::A))
	{
		Log::Debug() << "A";
	}
}