#pragma once

#include "Sea/Renderer/Window.hpp"

namespace Sea
{

	class Renderer;
	class Application;

	class Game
	{
	friend class Application;

	public:
		virtual void Before() { } 
		virtual void After() { }
		virtual void Update(f32 dt)=0;
		virtual void Render()=0;
		void Run();
		void Stop();
		f32 GetFPS();
		bool IsRunning();
		Window& GetWindow();
		const Renderer& GetRenderer();

		Game() = default;
		Game(const Game&) = default;
		Game(Game&&) = default;
		virtual ~Game() = default;
	
	private:
		void StartFPS();
		void EndFPS();

	private:
		bool m_isRunning = false;
		WindowPtr m_window;
		u32 startFPS, endFPS;
		f32 fps;
	};

}