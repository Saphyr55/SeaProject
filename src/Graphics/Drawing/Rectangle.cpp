#include "Sea/Graphics/Drawing/Rectangle.hpp"

namespace Sea
{
	void Rectangle::Position(s32 x, s32 y)
	{
		PosX(x);
		PosY(y);
	}
	
	void Rectangle::Size(s32 width, s32 height)
	{
		Width(width);
		Height(height);
	}

}