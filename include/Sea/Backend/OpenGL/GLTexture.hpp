#pragma once

#include <Sea/Backend/OpenGL/GL.hpp>
#include <Sea/Graphic/Shader.hpp>
#include <Sea/Graphic/Texture.hpp>
#include <Sea/Common/File.hpp>

namespace Sea
{	

	namespace Backend::OpenGL
	{

		class GLTexture : public Texture
		{
		public:
			void Bind();
			void Unbind();
			void Delete();

			GLTexture(File image, Type texType, u32 slot);
			~GLTexture() = default;

		private:
			void SetupFormatFromChannel(s32 channel);
			void SetDefaultParameteri();
		};

		using GLTexturePtr = Ref<GLTexture>;

	}
}
