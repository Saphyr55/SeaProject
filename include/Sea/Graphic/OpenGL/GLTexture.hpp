#pragma once

#include "Sea/Core/File.hpp"
#include "Sea/Graphic/OpenGL/GL.hpp"
#include "Sea/Graphic/Shaders/Shader.hpp"
#include "Sea/Graphic/Texture.hpp"
#include "Sea/Graphic/Mesh.hpp"
#include "Sea/Graphic/Rendering/Window.hpp"

namespace Sea::Backend::OpenGL
{	
	class GLTexture : public Texture
	{
	public:

		void Bind();
		void Unbind();
		void Delete();

		GLTexture(std::string_view path, Type texType, u32 slot);
		GLTexture(File image, Type texType, u32 slot);
		~GLTexture() = default;

	private:
		void SetupFormatFromChannel(s32 channel);
		void SetDefaultParameteri();
	};
}
