#include <Sea/Backend/OpenGL/GLElementBuffer.hpp>
#include <Sea/Backend/OpenGL/GL.hpp>

namespace Sea::Backend::OpenGL
{
	void GLElementBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void GLElementBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void GLElementBuffer::Delete()
	{
		glDeleteBuffers(1, &id);
	}

	GLElementBuffer::GLElementBuffer(u32 indices[], u32 size)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

}