#pragma once

#include "Sea/Renderer/Window.hpp"
#include "Sea/Context.hpp"

namespace Sea
{

	class Window;
	class Renderer;

	class Sea
	{
	public:
		void CreateWindow();
		void OnUpdate(float dt);
		void Run();

	public:
		Sea(ContextType context, Window& window);
		~Sea();

	private:
		bool m_isRunning;
		ContextType m_context;
		Window m_window;
	};
}