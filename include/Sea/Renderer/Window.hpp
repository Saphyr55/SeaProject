#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "Sea/Core/GameWindow.hpp"
#include "Sea/Core/IWindow.hpp"

namespace Sea
{
	class Window : public IWindow
	{	
	public:
		virtual void OnUpdate(float dt)=0;

		void Hide();
		void Show();
		void Close();
		bool IsOpen();
		bool IsClosed();

	public:
		Window(std::string title, int width, int height);
		~Window();

	protected:
		GameWindow m_handle;
		bool m_isOpen = true;
	};
}

