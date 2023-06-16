#pragma once

#include <memory>

#include "Sea/Graphics/OpenGL/GL.hpp"

namespace Sea::Backend::OpenGL
{
	class GLVertexBuffer;

	class GLVertexArray
	{
	SEA_PROPERTY_READONLY(Id, u32, id)

	public:
		void LinkVertexBuffer(GLVertexBuffer& vertexBuffer, u32 layout);
		void LinkVertexBuffer(GLVertexBuffer& vertexBuffer, u32 layout, u32 numComp, u32 type, u32 stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();

		GLVertexArray();
		~GLVertexArray() = default;
	};

	using GLVertexArrayPtr = std::shared_ptr<GLVertexArray>;

}