#pragma once

namespace Sea
{
	class Game
	{
	public:
		void OnUpdate(float dt) { }
		void OnRender() { }

	public:
		Game()=default;
		Game(Game&&) = default;
		Game(const Game&) = default;
		~Game()=default;

	private:

	};

}