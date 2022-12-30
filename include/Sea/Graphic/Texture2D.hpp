#pragma once

#include "Sea/Common/CommonType.hpp"
#include "Sea/Common/File.hpp"

namespace Sea
{
	class Texture2D
	{
	public:
		enum class Type
		{
			None = 0,
			Diffuse = 1,
			Specular = 2,
			Ambient = 3,
			Shininess = 4,
			Normal = 5
		};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;

		inline File GetFile() { return imageFile; }
		inline u32 GetId() { return id; };
		inline s32 GetWidth() { return width; };
		inline s32 GetHeight() { return height; };
		
		Texture2D(File image, Type texType, u32 slot);
		Texture2D(std::string_view path, Type texType, u32 slot);
		virtual ~Texture2D() = default;

	protected:
		File imageFile;
		s32 width;
		s32 height;
		u32 id;
		u32 format;
		u32 m_slot;
		u32 m_unit;

	public:
		const Type TextureType;
	};

}
