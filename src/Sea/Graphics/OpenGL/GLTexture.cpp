#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <stb/stb_image.h>
#include <fmt/core.h>

#include "Sea/Graphics/OpenGL/GLTexture.hpp"

namespace Sea
{

	GLTexture::GLTexture(std::string_view path, Type texType, u32 slot) : GLTexture(File(path), texType, slot) { }

	GLTexture::GLTexture(File image, Type texType, u32 slot) : Texture(image, texType, slot) {	}

	void GLTexture::Load()
	{	
		const auto* path_file = m_image_file.GetPath().c_str();
		if (!m_image_file.Exist())
		{
			fmt::print("Cannot load texture, reason : {} not exist.\n", path_file);
			throw;
		}

		s32 channel;
		u8* bytes = stbi_load(path_file, &m_width, &m_height, &channel, 0);
		if (bytes)
		{
			glGenTextures(1, &m_id);
			Bind();
			SetDefaultParameteri();
			SetupFormatFromChannel(channel);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, bytes);
			glGenerateMipmap(GL_TEXTURE_2D);
			Unbind();

			fmt::print("Loading texture success: {} .\n", path_file);
		}
		else
		{
			fmt::print("Loading texture fail: {} cannot read bytes.\n", path_file);
			throw;
		}
		stbi_image_free(bytes);
	}

	void GLTexture::SetupFormatFromChannel(s32 channel)
	{
		switch (channel)
		{
		case 4:
			m_format = GL_RGBA;
			break;
		case 3:
			m_format = GL_RGB;
			break;
		case 1:
			m_format = GL_RED;
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

#undef STB_IMAGE_IMPLEMENTATION
