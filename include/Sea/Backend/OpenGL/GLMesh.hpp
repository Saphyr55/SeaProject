#pragma once

#include <Sea/Graphic/Mesh.hpp>

namespace Sea::Backend::OpenGL
{
	class GLMesh : public Mesh
	{
	public:
		void Draw() override;
		void Add(f32 vertices[], u32 indices[]) override;
		void Delete() override;

	public:
		GLMesh();
		~GLMesh()=default;

	private:
		u32 vbo, vao, ebo;
	};
}