#pragma once

#include <Sea/Renderer/Renderer.hpp>

namespace Sea
{
	class Game
	{
	public:
		virtual void OnUpdate(float dt) abstract;
		virtual void OnRender(Renderer& renderer) abstract;
		inline void Run() { m_isRunning = true; }
		inline void Stop() { m_isRunning = false; }
		inline bool IsRunning() { return m_isRunning; }
		void UseVsync(bool use);


	public:
		Game()=default;
		~Game()=default;

	private:
		bool m_isRunning = false;
	};

}