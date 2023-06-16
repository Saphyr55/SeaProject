#include "Sea/Graphics/OpenGL/GLVertexBuffer.hpp"

namespace Sea::Backend::OpenGL
{
	GLVertexBuffer::GLVertexBuffer(std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}
	
	void GLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void GLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	void GLVertexBuffer::Delete()
	{
		glDeleteBuffers(1, &id);
	}
}


