#pragma once

#include "Sea/Core/Common.hpp"
#include "Sea/Graphics/Drawing/Sprite.hpp"
#include "Sea/Graphics/Rendering/Camera.hpp"
#include "Sea/Graphics/Shaders/Shader.hpp"
#include "Sea/Core/Color.hpp"

namespace Sea
{

	class Rectangle : public Sprite
	{
	public:
		void Draw() override;
		f32 GetPosX() const { return m_x; }
		f32 GetPosY() const { return m_y; }
		f32 GetWidth() const { return m_width; }
		f32 GetHeight() const { return m_height; }
		void SetWidth(f32 width) { m_width = width; }
		void SetHeight(f32 height) { m_height = height; }
		void SetPosX(f32 x) { m_x = x; }
		void SetPosY(f32 y) { m_y = y; }
		void SetPosition(f32 x, f32 y);
		void SetSize(f32 width, f32 height);

	public:
		Rectangle(Window& window, Shader& shader, Color color = Colors::Black);
		~Rectangle() = default;

	private:
		Color color;
		f32 m_x, m_y = 0;
		f32 m_width, m_height = 0;
		Shader& shader;
		Window& window;
	};
}