#pragma once

#include <Sea/Common/CommonType.hpp>
#include <Sea/Common/File.hpp>

namespace Sea
{
	class Texture
	{
	public:
		enum class Type
		{
			DIFFUSE, SPECULAR
		};

		virtual void Bind()=0;
		virtual void Unbind()=0;
		virtual void Delete()=0;
		inline u32 GetId() { return id; };
		inline s32 GetWidth() { return width; };
		inline s32 GetHeight() { return height; };
		
		Texture(File image, Type texType, u32 slot);
		virtual ~Texture() = default;

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
