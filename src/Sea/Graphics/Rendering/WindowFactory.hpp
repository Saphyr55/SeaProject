#pragma once

#include <string>
#include "Sea/Core/Common.hpp"

namespace Sea
{

	class Window;
	class VideoMode;

	class WindowFactory
	{
	public:
		Ref<Window> CreateOpenGLWindow(std::string_view title, VideoMode& proterties);
		
	};

}