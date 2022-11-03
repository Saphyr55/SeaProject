#include "Sea/Backend/OpenGL/GLTexture.hpp"

#include <string>
#include <mcl/Logger.hpp>
#include <stb/stb_image.h>

using mcl::Log;

namespace Sea::Backend::OpenGL
{

	GLTexture::GLTexture(std::string_view path, Type texType, u32 slot) :
		GLTexture(File(path), texType, slot)
	{
	}

	GLTexture::GLTexture(File image, Type texType, u32 slot)
		: Texture(image, texType, slot)
	{	
		if (!image.Exist())
		{	
			Log::Error() << "Cannot load texture, reason :" << imageFile.GetPath().c_str() << " not exist";
			throw std::exception("");
		}

		s32 channel;
		u8* bytes = stbi_load(imageFile.GetPath().c_str(), &width, &height, &channel, 0);
		if (bytes)
		{
			glGenTextures(1, &id);
			Bind();
			SetDefaultParameteri();
			SetupFormatFromChannel(channel);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
			glGenerateMipmap(GL_TEXTURE_2D);
			Unbind();
			Log::Info() << "Loading texture success: " << imageFile.GetPath();
		}
		else
		{
			Log::Error() << imageFile.GetPath().c_str() << " cannot read bytes";
			throw std::exception("");
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
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void GLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLTexture::Delete()
	{
		glDeleteTextures(1, &id);
	}

}
