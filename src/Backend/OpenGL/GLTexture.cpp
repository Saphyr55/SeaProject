#include <Sea/Backend/OpenGL/GLTexture.hpp>
#include <Sea/Graphic/Shader.hpp>
#include <string>
#include <stb/stb_image.h>

namespace Sea::Backend::OpenGL
{
	GLTexture::GLTexture(File& image, u32 texType, u32 slot, u32 format, u32 pixelType)
		: imageFile(image), m_type(texType), m_format(format), m_slot(slot), m_pixelType(pixelType)
	{
		s32 channel;
		u8* bytes = stbi_load(imageFile.GetPath().c_str(), &width, &height, &channel, 0);

		glGenTextures(1, &id);
		glActiveTexture(slot);
		Bind();

		glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(m_type, 0, GL_RGBA, width, height, 0, format, m_pixelType, bytes);
		glGenerateMipmap(m_type);

		stbi_image_free(bytes);
		Unbind();
	}

	void GLTexture::TexUnit(ShaderPtr shader, const char* uniform, u32 unit)
	{	
		u32 tex0Uni = glGetUniformLocation(shader->GetId(), "tex0");
		shader->Use();
		glUniform1i(tex0Uni, 0);
	}

	void GLTexture::Bind()
	{
		glBindTexture(m_type, id);
	}

	void GLTexture::Unbind()
	{
		glBindTexture(m_type, 0);
	}

	void GLTexture::Delete()
	{
		glDeleteTextures(1, &id);
	}

	u32 GLTexture::GetId()
	{
		return id;
	}

	s32 GLTexture::GetWidth()
	{
		return width;
	}

	s32 GLTexture::GetHeight()
	{
		return height;
	}

}
