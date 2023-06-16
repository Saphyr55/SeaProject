#pragma once

#include "Sea/Core/Common.hpp"

namespace Sea
{
	class Rectangle
	{

	SEA_PROPERTY(PosX, s32, x, m_x)
	SEA_PROPERTY(PosY, s32, y, m_y)
	SEA_PROPERTY(Width, s32, width, m_width)
	SEA_PROPERTY(Height, s32, m_width, m_height)

	public:
		void Position(s32 x, s32 y);
		void Size(s32 width, s32 height);

	public: 
		Rectangle() = default;
		virtual ~Rectangle() = default;

	};
}