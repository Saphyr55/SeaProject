#pragma once

#include <memory>
#include <vector>

#include "Sea/Graphics/OpenGL/GL.hpp"
#include "Sea/Graphics/Vertex.hpp"

namespace Sea
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