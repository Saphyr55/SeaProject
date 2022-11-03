#pragma once

#include <string>
#include "Sea/Common/CommonType.hpp"

namespace Sea
{   
	enum class GraphicsAPI
	{
        OpenGL
	};

    struct VideoMode
    {
		u32 Width = 1080;
		u32 Height = 720;
		bool Resizable = false;
		bool Fullscreen = false;
		bool Maximazed = false;
    };

}
