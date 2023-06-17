#pragma once

#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea
{
	class GLWindow final : public Window
	{
	public:
		void Init();
		void Swap();
		void UseVSync(bool use);
		void Viewport();
		void Viewport(u32 h, u32 w);
		void Viewport(u32 x, u32 y, u32 h, u32 w);

	public:
		GLWindow(std::string_view title, VideoMode& proterties);
		~GLWindow() = default;
	};

}