#include <Sea/Backend/OpenGL/GLVertexBuffer.hpp>

namespace Sea::Backend::OpenGL
{
	GLVertexBuffer::GLVertexBuffer(f32 vertices[], u32 size)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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


