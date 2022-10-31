#pragma once

#include <memory>
#include <vector>
#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Graphic/Vertex.hpp>

namespace Sea::Backend::OpenGL
{

	class GLVertexBuffer
	{
	public:
		GLVertexBuffer(std::vector<Vertex>& vertices);
		~GLVertexBuffer()=default;

		void Bind();
		void Unbind();
		void Delete();

	private:
		u32 id;
	};
	using GLVertexBufferPtr = std::shared_ptr<GLVertexBuffer>;

}