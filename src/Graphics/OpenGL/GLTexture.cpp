#include <string>
#include <stb/stb_image.h>
#include <fmt/printf.h>

#include "Sea/Graphics/OpenGL/GLTexture.hpp"

namespace Sea::Backend::OpenGL
{

	GLTexture::GLTexture(std::string_view path, Type texType, u32 slot) : GLTexture(File(path), texType, slot) { }

	GLTexture::GLTexture(File image, Type texType, u32 slot) : Texture(image, texType, slot)
 	{	
		if (!image.Exist())
		{	
			fmt::print("Cannot load texture, reason :{} not exist.\n", m_image_file.GetPath().c_str());
			throw std::exception("");
		}

		s32 channel;
		u8* bytes = stbi_load(m_image_file.GetPath().c_str(), &m_width, &m_height, &channel, 0);
		if (bytes)
		{
			glGenTextures(1, &m_id);
			Bind();
			SetDefaultParameteri();
			SetupFormatFromChannel(channel);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, bytes);
			glGenerateMipmap(GL_TEXTURE_2D);
			Unbind();

			fmt::print("Loading texture success: {} .\n", m_image_file.GetPath());
		}
		else
		{
			fmt::print("{} cannot read bytes.\n", m_image_file.GetPath().c_str());
			throw std::exception();
		}
		stbi_image_free(bytes);
	}

	void GLTexture::SetupFormatFromChannel(s32 channel)
	{
		switch (channel)
		{
		case 4:
			format = GL_RGBA;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 1:
			format = GL_RED;
			break;
		default:
			throw std::exception("Automatic Texture type recognition failed");
		}
	}

	void GLTexture::SetDefaultParameteri()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void GLTexture::Bind()
	{
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void GLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLTexture::Delete()
	{
		glDeleteTextures(1, &m_id);
	}

	

}
