#pragma once

#include "Sea/Core/Common.hpp"
#include "Sea/Graphics/Drawing/Drawable.hpp"
#include "Sea/Graphics/Rendering/Camera.hpp"
#include "Sea/Graphics/Shaders/Shader.hpp"
#include "Sea/Core/Color.hpp"

namespace Sea
{

	struct ShapeProperties
	{

	};

	class Shape : public Drawable
	{

	public:
		void Draw() override;
		Ref<Mesh> GetMesh() { return m_mesh; }
		f32 GetPosX() const { return m_x; }
		f32 GetPosY() const { return m_y; }
		f32 GetWidth() const { return m_width; }
		f32 GetHeight() const { return m_height; }
		void SetWidth(f32 width) { m_width = width; }
		void SetHeight(f32 height) { m_height = height; }
		void SetPosX(f32 x) { m_x = x; }
		void SetPosY(f32 y) { m_y = y; }
		void SetPosition(f32 x, f32 y) { SetPosX(x); SetPosY(y); }
		void SetSize(f32 width, f32 height) { SetWidth(width); SetHeight(height); }

	public:
		Shape(Window& parent, Color color = Colors::Black);
		~Shape() = default;

	private:
		f32 m_x, m_y, m_width, m_height = 0;
		Ref<Mesh> m_mesh;
		Color color;
		Window& parent;
	};
}