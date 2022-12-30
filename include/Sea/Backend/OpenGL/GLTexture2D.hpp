#pragma once

#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Graphic/Shader.hpp"
#include "Sea/Graphic/Texture2D.hpp"
#include "Sea/Common/File.hpp"

namespace Sea::Backend::OpenGL
{	
	class GLTexture2D : public Texture2D
	{
	public:

		void Bind();
		void Unbind();
		void Delete();
		
		GLTexture2D(std::string_view path, Type texType, u32 slot);
		GLTexture2D(File image, Type texType, u32 slot);
		~GLTexture2D() = default;

	private:
		void SetupFormatFromChannel(s32 channel);
		void SetDefaultParameteri();
	};
}
