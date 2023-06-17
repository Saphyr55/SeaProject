#include <Sea/Graphics/OpenGL/GLVertexArray.hpp>
#include <Sea/Graphics/OpenGL/GLVertexBuffer.hpp>

namespace Sea
{

	GLVertexArray::GLVertexArray()
	{
        glGenVertexArrays(1, &m_id);
    }

	void GLVertexArray::LinkVertexBuffer(GLVertexBuffer& vertexBuffer, u32 layout, u32 numComp, u32 type, u32 stride, void* offset)
	{
		vertexBuffer.Bind();
		glVertexAttribPointer(layout, numComp, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		vertexBuffer.Unbind();
	}

    void GLVertexArray::LinkVertexBuffer(GLVertexBuffer& vertexBuffer, u32 layout)
    {
        vertexBuffer.Bind();
        glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE ,0, (void*)0);
        glEnableVertexAttribArray(layout);
        vertexBuffer.Unbind();
    }

    void GLVertexArray::Bind()
    {
        glBindVertexArray(m_id);
    }
    
    void GLVertexArray::Unbind()
    {
		glBindVertexArray(0);
    }
    
    void GLVertexArray::Delete()
    {
        glDeleteVertexArrays(1, &m_id);
    }

}