#pragma once

#include "Sea/Core/Result.hpp"
#include "Sea/Core/Common.hpp"
#include "Sea/Core/File.hpp"

namespace Sea
{

	class Texture
	{

	public:
		enum class Error
		{
			TextureNotExist,
			LoadingBytes,
		};

		enum class Type
		{
			None = 0,
			Diffuse = 1,
			Specular = 2,
			Ambient = 3,
			Shininess = 4,
			Normal = 5
		};

		virtual void Load() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;
		
		u32 GetId() const { return m_id; }
		s32 GetWidth() const { return m_width; }
		s32 GetHeight() const { return m_height; }
		const File& GetFile() const { return m_image_file; }

	public:
		Texture(File image, Type texType, u32 slot);
		Texture(std::string_view path, Type texType, u32 slot);
		virtual ~Texture() = default;

	protected:
		File m_image_file;
		u32 m_format;
		u32 m_slot;
		u32 m_unit;
		u32 m_id;
		s32 m_width;
		s32 m_height;

	public:
		const Type TextureType;
	};

	using TextureRef = Ref<Texture>;

}
