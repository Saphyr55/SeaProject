#pragma once

#include <memory>
#include <Sea/Backend/OpenGL/GL.hpp>

namespace Sea::Backend::OpenGL
{
	class GLVertexBuffer
	{
	public:
		GLVertexBuffer(f32 vertices[], u32 size);
		~GLVertexBuffer()=default;

		void Bind();
		void Unbind();
		void Delete();

	private:
		u32 id;
	};
	using GLVertexBufferPtr = std::shared_ptr<GLVertexBuffer>;

}