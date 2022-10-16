#pragma once

namespace Sea
{
	class Game
	{
	public:
		void OnUpdate(float dt) { }
		void OnRender() { }
		inline void Run() { m_isRunning = true; }
		inline void Stop() { m_isRunning = false; }
		inline bool IsRunning() { return m_isRunning; }

	public:
		Game()=default;
		Game(Game&&) = default;
		Game(const Game&) = default;
		~Game()=default;

	private:
		bool m_isRunning = false;
	};

}