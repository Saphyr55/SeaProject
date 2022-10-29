#pragma once

#include <memory>
#include <Sea/Backend/OpenGL/GL.hpp>

namespace Sea::Backend::OpenGL
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

		GLVertexArray();
		~GLVertexArray()=default;

	private:
		u32 id;
	};

	using GLVertexArrayPtr = std::shared_ptr<GLVertexArray>;

}