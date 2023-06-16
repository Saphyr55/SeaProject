#pragma once

#include "Sea/Core/Common.hpp"
#include "Sea/Core/File.hpp"

namespace Sea
{

	class Texture
	{

	SEA_PROPERTY_READONLY(TextureFile, File, m_image_file)
	SEA_PROPERTY_READONLY(Id, u32, m_id)
	SEA_PROPERTY_READONLY(Width, s32, m_width)
	SEA_PROPERTY_READONLY(Height, s32, m_height)

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
	
		Texture(File image, Type texType, u32 slot);
		Texture(std::string_view path, Type texType, u32 slot);
		virtual ~Texture() = default;

	protected:
		u32 format;
		u32 m_slot;
		u32 m_unit;

	public:
		const Type TextureType;
	};

	using TextureRef = Ref<Texture>;

}
