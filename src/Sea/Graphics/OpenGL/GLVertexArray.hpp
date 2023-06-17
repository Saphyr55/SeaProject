#pragma once

#include <memory>

#include "Sea/Graphics/OpenGL/GL.hpp"

namespace Sea
{
	class GLVertexBuffer;

	class GLVertexArray
	{

	public:
		void LinkVertexBuffer(GLVertexBuffer& vertexBuffer, u32 layout);
		void LinkVertexBuffer(GLVertexBuffer& vertexBuffer, u32 layout, u32 numComp, u32 type, u32 stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
		u32 Id() const { return m_id; }

		GLVertexArray();
		~GLVertexArray() = default;
	
	private:
		u32 m_id;
	};

	using GLVertexArrayRef = Ref<GLVertexArray>;

}