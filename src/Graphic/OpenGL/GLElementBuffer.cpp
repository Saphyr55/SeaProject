#include <Sea/Graphic/OpenGL/GLElementBuffer.hpp>
#include <Sea/Graphic/OpenGL/GL.hpp>

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

	GLElementBuffer::GLElementBuffer(std::vector<u32>& indices)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), indices.data(), GL_STATIC_DRAW);
	}

}