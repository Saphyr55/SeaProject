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
		Color Colour = Colors::Black;
		f32 Edge = 1.0f;
		f32 Border;
		f32 BorderRadiusTopLeft;
		f32	BorderRadiusTopRight;
		f32	BorderRadiusBottomLeft;
		f32	BorderRadiusBottomRight;
	};

	class Shape : public Drawable
	{

	public:
		virtual void Draw() override;
		ShapeProperties& GetShapeProperties() { return m_properties; }
		Ref<Mesh> GetMesh() { return m_mesh; }
		f32 GetDepth() const { return m_depth; }
		f32 GetPosX() const { return m_x; }
		f32 GetPosY() const { return m_y; }
		f32 GetWidth() const { return m_width; }
		f32 GetHeight() const { return m_height; }
		const f32* GetRelativeWidth() const { return m_relative_width; }
		const f32* GetRelativeHeight() const { return m_relative_height; }
		void SetWidth(f32 width) { m_width = width; }
		void SetHeight(f32 height) { m_height = height; }
		void SetPosX(f32 x) { m_x = x; }
		void SetPosY(f32 y) { m_y = y; }
		void SetPosition(f32 x, f32 y) { SetPosX(x); SetPosY(y); }
		void SetSize(f32 width, f32 height) { SetWidth(width); SetHeight(height); }
		void SetRelative(f32& width, f32& height);
		void SetDepth(f32 depth) { m_depth = depth; }

	private:
		void Shadering(Shader& shader);

	public:
		Shape(Color color = Colors::Black);
		~Shape() = default;

	protected:
		static f32 depth_static;
		ShapeProperties m_properties;
		Ref<Mesh> m_mesh;
		Color color;
		f32 m_depth = 0;
		f32 m_x = 0;
		f32 m_y = 0;
		f32 m_width = 0; 
		f32 m_height = 0;
		f32* m_relative_width;
		f32* m_relative_height;
	};
}