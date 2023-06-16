#pragma once

#include "Sea/Core/Common.hpp"
#include "Sea/Graphics/Drawing/Sprite.hpp"
#include "Sea/Graphics/Drawing/Rectangle.hpp"
#include "Sea/Graphics/Rendering/Camera.hpp"
#include "Sea/Graphics/Shaders/Shader.hpp"

namespace Sea
{

	class Box : public Sprite, public Rectangle
	{
	SEA_ATTRIBUTE(Shader&, shader)
	SEA_ATTRIBUTE(Window&, window)

	public:
		void Draw();


	public:
		Box(Window& window, Shader& shader);
		~Box() = default;


	};
}