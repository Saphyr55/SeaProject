#pragma once

#include "Sea/Backend/OpenGL/GL.hpp"
#include "Sea/Graphic/Shader.hpp"
#include "Sea/Graphic/Texture.hpp"
#include "Sea/Common/File.hpp"
#include <Sea/Renderer/Window.hpp>
#include <Sea/Graphic/Mesh.hpp>

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
