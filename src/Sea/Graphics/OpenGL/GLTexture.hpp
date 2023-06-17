#pragma once

#include "Sea/Core/File.hpp"
#include "Sea/Graphics/OpenGL/GL.hpp"
#include "Sea/Graphics/Shaders/Shader.hpp"
#include "Sea/Graphics/Texture.hpp"
#include "Sea/Graphics/Mesh.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea
{	

	class GLTexture : public Texture
	{
	public:
		void Load() override;
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
