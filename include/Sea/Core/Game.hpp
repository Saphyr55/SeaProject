#pragma once

#include "Sea/Renderer/Window.hpp"

namespace Sea
{
	using WindowPtr = std::shared_ptr<Window>;

	class Renderer;
	class Engine;

	class Game
	{
	friend class Engine;

	public:
		virtual void Before() { } 
		virtual void After() { }
		virtual void Update(float dt)=0;
		virtual void Render()=0;
		void Run();
		void Stop();
		bool IsRunning();
		Window& GetWindow();
		const Renderer& GetRenderer();

		Game() = default;
		Game(const Game&) = default;
		Game(Game&&) = default;
		virtual ~Game() = default;

	private:
		bool m_isRunning = false;
		WindowPtr m_window;
	};

}